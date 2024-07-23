#include "Helper.h"
#include "RouteGuideCallbackServer.h"


#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/server_builder.h>
#include <string>
//
// Created by tuantq3 on 23/07/2024.
//
void RunRoutGuideCallbackServer(const std::string &db_path) {
    std::string server_address{"0.0.0.0:1943"};
    RouteGuideCallbackServer callback_server{db_path};
    grpc::EnableDefaultHealthCheckService(true);

    grpc::ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&callback_server);
    // Finally assemble the server.
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}
int main(int argc, char *argv[]) {
    std::string db = Helper::GetDbFileContent(argc, argv);
    RunRoutGuideCallbackServer(db);
    return 0;
}