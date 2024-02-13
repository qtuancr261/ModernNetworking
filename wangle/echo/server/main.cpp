#include "EchoServer.h"
#include "folly/init/Init.h"
#include "wangle/bootstrap/ServerBootstrap.h"
#include "wangle/ssl/SSLContextConfig.h"
#include "wangle/ssl/TLSCredProcessor.h"

DEFINE_string(cert_path, "", "Path to cert pem");
DEFINE_string(key_path, "", "Path to cert key");
DEFINE_string(ca_path, "", "Path to trusted CA file");
DEFINE_int32(port, 8080, "Server port");
DEFINE_string(tickets_path, "", "Path for ticket seeds");
DEFINE_uint32(num_workers, 2, "Number of worker threads");
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
            std::cout << "Reload SSLContext configs - shared all thread" << std::endl;
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
                    std::cout << "Reset SSLContext configs - per acceptor thread" << std::endl;
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

    wangle::ServerSocketConfig socketConfig;
    folly::Optional<wangle::TLSTicketKeySeeds> seeds;
    wangle::TLSCredProcessor tlsCredProcessor;
    if (!FLAGS_tickets_path.empty()) {
        seeds = wangle::TLSCredProcessor::processTLSTickets(FLAGS_tickets_path);
        if (seeds) {
            socketConfig.initialTicketSeeds = *seeds;
            // watch for changes
            tlsCredProcessor.setTicketPathToWatch(FLAGS_tickets_path);
        }
    }
    if (!FLAGS_cert_path.empty() && !FLAGS_key_path.empty()) {
        LOG(INFO) << "Configuring SSL/TLS certificates";
        wangle::SSLContextConfig sslContextConfig;
        // only one SSLContextConfig must be default
        sslContextConfig.isDefault = true;
        sslContextConfig.addCertificate(FLAGS_cert_path, FLAGS_key_path, "");
        sslContextConfig.clientCAFiles = std::vector<std::string>{FLAGS_ca_path};
        sslContextConfig.clientVerification = folly::SSLContext::VerifyClientCertificate::IF_PRESENTED;
        // addtional ALPN for this SSL context config
        // the EchoHandler can actually read HTTP/1.1 request from curl (thanks to the plaintext protocol of HTTP/1.1)
        // > GET /page/ HTTP/1.1 \r\n
        // > Host: sampledomain.doc:8080 \r\n
        // > User-Agent: curl/7.81.0 \r\n
        // > Accept: */* \r\n
        // > Accept-Encoding: br \r\n
        // > \r\n
        std::list<std::string> nextProtocols{"h2", "http/1.1"};
        sslContextConfig.setNextProtocols(nextProtocols);

        socketConfig.sslContextConfigs.push_back(sslContextConfig);
        // IMPORTANT: when allowing both plaintext and ssl on the same port,
        // the acceptor requires 9 bytes of data to determine what kind of
        // connection is coming in.
        // If the client does not send 9 bytes, the
        // connection will idle out before the EchoCallback receives data.
        socketConfig.allowInsecureConnectionsOnSecureServer = false;
        // reload SSL contexts when cert changes
        std::set<std::string> pathsToWatch{FLAGS_cert_path, FLAGS_key_path};
        if (!FLAGS_ca_path.empty()) {
            pathsToWatch.insert(FLAGS_ca_path);
        }
        tlsCredProcessor.setCertPathsToWatch(std::move(pathsToWatch));
    }

    initCredProcessorCallbacks(echoServer, tlsCredProcessor);
    auto workers = std::make_shared<folly::IOThreadPoolExecutor>(FLAGS_num_workers);

    // must be set in this order
    // ssl acceptor -> pipeline -> worker -> bind
    echoServer.acceptorConfig(socketConfig);
    echoServer.childPipeline(std::make_shared<EchoPipeLineFactory>());
    echoServer.setUseSharedSSLContextManager(FLAGS_enable_share_ssl_ctx);
    echoServer.group(workers);

    echoServer.bind(FLAGS_port);
    echoServer.waitForStop();
    return 0;
}
