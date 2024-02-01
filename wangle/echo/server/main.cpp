#include "EchoServer.h"
#include "folly/init/Init.h"
#include "wangle/bootstrap/ServerBootstrap.h"
#include "wangle/ssl/SSLContextConfig.h"
#include "wangle/ssl/TLSCredProcessor.h"
DEFINE_int32(port, 8080, "Server port");
DEFINE_bool(enable_share_ssl_ctx, true, "Enable sharing SSL context configs between worker threads");

void initCredProcessorCallbacks(wangle::ServerBootstrap<EchoPipeLine> &serverBootstrap, wangle::TLSCredProcessor &tlsCredProcessor) {
    // setup ticket seed callback
    tlsCredProcessor.addTicketCallback([&](wangle::TLSTicketKeySeeds seeds) {
        if (FLAGS_enable_share_ssl_ctx) {
            serverBootstrap.getSharedSSLContextManager()->updateTLSTicketKeys(seeds);
        } else {
            // update
            serverBootstrap.forEachWorker([&](wangle::Acceptor *acceptor) {
                if (!acceptor) {
                    // this condition can happen if the processor triggers before the server is ready/listening
                    return;
                } else {
                    auto evb = acceptor->getEventBase();
                    if (!evb) {
                        return;
                    }
                    evb->runInEventBaseThread([acceptor, seeds]() {
                        acceptor->setTLSTicketSecrets(seeds.oldSeeds, seeds.currentSeeds, seeds.newSeeds);
                    });
                }
            });
        }
    });
    // reconfigure TLS/SSL when we detect cert or CA changes
    tlsCredProcessor.addCertCallback([&]() {
        if (FLAGS_enable_share_ssl_ctx) {
            serverBootstrap.getSharedSSLContextManager()->reloadSSLContextConfigs();
        } else {
            serverBootstrap.forEachWorker([&](wangle::Acceptor *acceptor) {
                if (!acceptor) {
                    return;
                }
                auto evb = acceptor->getEventBase();
                if (!evb) {
                    return;
                }
                evb->runInEventBaseThread([acceptor]() {
                    acceptor->resetSSLContextConfigs();
                });
            });
        }
    });
}
int main(int argc, char *argv[]) {
    folly::Init init(&argc, &argv);
    // simple echo client - server
    wangle::ServerBootstrap<EchoPipeLine> echoServer;
    echoServer.childPipeline(std::make_shared<EchoPipeLineFactory>());
    echoServer.bind(FLAGS_port);
    echoServer.waitForStop();
    return 0;
}
