#include "EchoServer.h"
#include "wangle/bootstrap/ServerBootstrap.h"
DEFINE_int32(port, 8080, "Server port");
int main(int argc, char *argv[]) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    wangle::ServerBootstrap<EchoPipeLine> echoServer;
    echoServer.childPipeline(std::make_shared<EchoPipeLineFactory>());
    echoServer.bind(FLAGS_port);
    echoServer.waitForStop();
    return 0;
}
