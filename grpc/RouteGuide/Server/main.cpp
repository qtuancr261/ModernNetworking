//
// Created by tuantq on 15/04/2024.
//
#include "Helper.h"
#include "RouteGuideServer.h"
#include <grpcpp/server_builder.h>
#include <iostream>
#include <thread>

void RunSyncRouteGuideServer(const std::string &db_path) {
    std::string server_address{"0.0.0.0:1943"};
    RouteGuideServer syncService{db_path};
    grpc::ServerBuilder serverBuilder;
    //
    grpc::ResourceQuota resourceQuota;
    resourceQuota.SetMaxThreads(std::thread::hardware_concurrency());
    serverBuilder.SetResourceQuota(resourceQuota);
    serverBuilder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    serverBuilder.RegisterService(&syncService);
    std::unique_ptr<grpc::Server> server(serverBuilder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}
int main(int argc, char *argv[]) {
    std::string db = Helper::GetDbFileContent(argc, argv);
    RunSyncRouteGuideServer(db);
    return 0;
}