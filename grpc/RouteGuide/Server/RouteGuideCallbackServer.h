//
// Created by tuantq3 on 23/07/2024.
//

#ifndef ROUTEGUIDECALLBACKSERVER_H
#define ROUTEGUIDECALLBACKSERVER_H
#include "gen-cpp/route_guide.grpc.pb.h"
#include "gen-cpp/route_guide.pb.h"

/**
 * @brief gRPC async/callback APIs server
 * based on gRPC C++ hellword async server example: greeter_async_server.cc
 */
class RouteGuideCallbackServer : public routeguide::RouteGuide::CallbackService {
public:
    explicit RouteGuideCallbackServer(const std::string& db);
    /**
     * @brief 
     * @return reactor model for unary RPCs
     */
    grpc::ServerUnaryReactor *GetFeature(grpc::CallbackServerContext *, const routeguide::Point *, routeguide::Feature *) override;
    /**
     * @brief 
     * @return reactor model for server-streaming RPCs 
     */
    grpc::ServerWriteReactor<routeguide::Feature> *ListFeatures(grpc::CallbackServerContext *, const routeguide::Rectangle *) override;
    /**
     * @brief 
     * @return reactor model for client-streaming RPCs
     */
    grpc::ServerReadReactor<routeguide::Point> *RecordRoute(grpc::CallbackServerContext *, routeguide::RouteSummary *) override;
    /**
     * @brief 
     * @return reactor model for bidi-streaming RPCs
     */
    grpc::ServerBidiReactor<routeguide::RouteNote, routeguide::RouteNote> *RouteChat(grpc::CallbackServerContext *) override;

private:
    std::vector<routeguide::Feature> features_;
    std::mutex mutex_;
    std::vector<routeguide::RouteNote> receivedRouteNotes_;
};


#endif//ROUTEGUIDECALLBACKSERVER_H
