#include "EchoClient.h"
#include "wangle/bootstrap/ClientBootstrap.h"
#include "folly/init/Init.h"
#include <iostream>
DEFINE_string(host, "::", "");
DEFINE_uint32(port, 8080, "");
int main(int argc, char *argv[]) {
    folly::Init init(&argc, &argv);
    wangle::ClientBootstrap<EchoPipeLine> client;
    client.group(std::make_shared<folly::IOThreadPoolExecutor>(1));
    client.pipelineFactory(std::make_shared<EchoPipeLineFactory>());
    auto pipeline = client.connect(folly::SocketAddress(FLAGS_host, FLAGS_port)).get();

    try {
        while (true) {
            std::string line;
            std::getline(std::cin, line);
            if (line.empty()) {
                break;
            }

            pipeline->write(line + "\r\n").get();
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
