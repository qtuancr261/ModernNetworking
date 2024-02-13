#include "EchoClient.h"
#include "folly/init/Init.h"
#include "folly/ssl/Init.h"
#include "folly/io/async/AsyncSocket.h"
#include "folly/io/async/SSLContext.h"
#include "wangle/bootstrap/ClientBootstrap.h"
#include "wangle/ssl/SSLContextConfig.h"
#include <iostream>
DEFINE_string(host, "::", "");
DEFINE_uint32(port, 8080, "");
DEFINE_string(cert_path, "", "Path to client cert pem");
DEFINE_string(key_path, "", "Path to client cert key pem");
DEFINE_string(ca_path, "", "Path to trusted CA file");
DEFINE_bool(secure_ssl, false, "Whether to use SSL");

const std::string SESSION_KEY{"test_client"};
class EchoClientBootstrap : public wangle::ClientBootstrap<EchoPipeLine> {
public:
    void makePipeline(std::shared_ptr<folly::AsyncTransport> socket) override {
        //        BaseClientBootstrap::makePipeline(socket);
        auto sslSocket = socket->getUnderlyingTransport<folly::AsyncSSLSocket>();
        if (sslSocket) {
            sslSocket->setSessionKey(SESSION_KEY);
        }
        // this will call PipeLineFactory::newPipeline -> we can set a session key from there,
        // but I think they choose a better way to implement it in ClientBootstrap::makePipeline
        wangle::ClientBootstrap<EchoPipeLine>::makePipeline(std::move(socket));
    }
};

std::shared_ptr<folly::SSLContext> createSSLContext() {
    auto context = std::make_shared<folly::SSLContext>();
    if (!FLAGS_ca_path.empty()) {
        context->loadTrustedCertificates(FLAGS_ca_path.c_str());
        // don't do peer name validation
        context->authenticate(true, false);
        // verify the server cert
        context->setVerificationOption(folly::SSLContext::SSLVerifyPeerEnum::VERIFY);
    }
    if (!FLAGS_cert_path.empty() && !FLAGS_key_path.empty()) {
        context->loadCertificate(FLAGS_cert_path.c_str());
        context->loadPrivateKey(FLAGS_key_path.c_str());
        if (!context->isCertKeyPairValid()) {
            throw std::runtime_error("Cert and key do not match");
        }
    }
    folly::ssl::setSignatureAlgorithms<folly::ssl::SSLCommonOptions>(*context);
    return context;
};
int main(int argc, char *argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    EchoClientBootstrap client;
    client.group(std::make_shared<folly::IOThreadPoolExecutor>(1));
    client.pipelineFactory(std::make_shared<EchoPipeLineFactory>());
    if (FLAGS_secure_ssl) {
        std::cout << "Establishing secure connection" << std::endl;
        auto sslCtx = createSSLContext();
        client.sslContext(sslCtx);
    }
    LOG(INFO) << "connecting to server";
    auto pipeline = client.connect(folly::SocketAddress(FLAGS_host, FLAGS_port)).get();
    LOG(INFO) << "connected to server";
    try {
        while (true) {
            std::string line;
            std::getline(std::cin, line);
            if (line.empty()) {
                break;
            }

            pipeline->write(line + "\r\n");
            if (line == "bye") {
                pipeline->close();
                break;
            }
        }
    } catch (const std::exception &e) {
        std::cout << folly::exceptionStr(e) << std::endl;
    }
    return 0;
}
