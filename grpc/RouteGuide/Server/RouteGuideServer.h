//
// Created by tuantq on 16/04/2024.
//

#ifndef ROUTEGUIDESERVER_H
#define ROUTEGUIDESERVER_H

#include "gen-cpp/route_guide.grpc.pb.h"
#include "gen-cpp/route_guide.pb.h"
/**
 * @brief synchronous version of RouteGuide::Service
 */
class RouteGuideServer final : public routeguide::RouteGuide::Service {
public:
    explicit RouteGuideServer(const std::string& db);
public:
    // all service methods can (and will) be called from multiple threads at the same time
    // Make sure that our method implemetations are THREAD SAFE
    /**
     * @brief simple RPC method
     * @param context
     * @param request client's Point protocol buffer request
     * @param response Feature protocol buffer to fill in with the response
     * @return OK status to tell gRPC that we've finished dealing with the RPC and the response can be returned to the client.
     */
    grpc::Status GetFeature(grpc::ServerContext *context, const routeguide::Point *request, routeguide::Feature *response) override;
    /**
     * @brief streaming RPC method - a bit more complicated
     * @param context
     * @param request client's Rectangle protocol buffer request
     * @param writer ServerWriter to populate as many Feature objects as we have to return
     * @return OK status to tell gRPC that we've finished writing responses.
     */
    grpc::Status ListFeatures(grpc::ServerContext *context, const routeguide::Rectangle *request, grpc::ServerWriter<routeguide::Feature> *writer) override;
    grpc::Status RecordRoute(grpc::ServerContext *context, grpc::ServerReader<routeguide::Point> *reader, routeguide::RouteSummary *response) override;
    grpc::Status RouteChat(grpc::ServerContext *context, grpc::ServerReaderWriter<routeguide::RouteNote, routeguide::RouteNote> *stream) override;

public:
    static float convertToRadians(float num);
    static float getDistance(const routeguide::Point &start, const routeguide::Point &end);
    static std::string getFeatureName(const routeguide::Point &point,
                                      const std::vector<routeguide::Feature> &feature_list);
private:
    std::vector<routeguide::Feature> features_;
    std::mutex mutex_;
    std::vector<routeguide::RouteNote> receivedRouteNotes_;
};


#endif//ROUTEGUIDESERVER_H
