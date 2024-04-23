//
// Created by tuantq3 on 22/04/2024.
//

#ifndef ROUTEGUIDECLIENT_H
#define ROUTEGUIDECLIENT_H
#include "gen-cpp/route_guide.grpc.pb.h"
#include "gen-cpp/route_guide.pb.h"


class RouteGuideClient {
public:
    RouteGuideClient(std::shared_ptr<grpc::Channel> channel, const std::string &db);
    static routeguide::Point MakePoint(long latitude, long longitude);
    static routeguide::Feature MakeFeature(const std::string &name, long latitude, long longitude);
    static routeguide::RouteNote MakeRouteNote(const std::string &message, long latitude, long longitude);

    void GetFeature();
    void ListFeatures();
    void RecordRoute();
    void RouteChat();
private:
    bool GetOneFeature(const routeguide::Point &point, routeguide::Feature *feature);


private:
    const float kCoordFactor_ = 10000000.0;
    std::unique_ptr<routeguide::RouteGuide::Stub> stub_;
    std::vector<routeguide::Feature> features_;
};


#endif//ROUTEGUIDECLIENT_H
