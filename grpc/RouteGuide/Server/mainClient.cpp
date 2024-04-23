//
// Created by tuantq3 on 22/04/2024.
//
#include "Helper.h"
#include "RouteGuideClient.h"
#include <grpcpp/create_channel.h>

#include <grpcpp/channel.h>

int main(int argc, char *argv[]) {
    std::string db = Helper::GetDbFileContent(argc, argv);
    RouteGuideClient guideClient{grpc::CreateChannel("0.0.0.0:1943",
                                                     grpc::InsecureChannelCredentials()),
                                 db};
    for (int i{}; i < 1; ++i) {
        std::cout << "-------------- GetFeature --------------" << std::endl;
        guideClient.GetFeature();
        std::cout << "-------------- ListFeatures --------------" << std::endl;
        guideClient.ListFeatures();
        std::cout << "-------------- RecordRoute --------------" << std::endl;
        guideClient.RecordRoute();
        std::cout << "-------------- RouteChat --------------" << std::endl;
        guideClient.RouteChat();
    }
    return 0;
}