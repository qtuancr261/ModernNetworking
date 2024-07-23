//
// Created by tuantq3 on 23/07/2024.
//

#include "RouteGuideUnaryReactor.h"

#include "../RouteGuideServer.h"
RouteGuideUnaryReactor::RouteGuideUnaryReactor(const routeguide::Point &point, routeguide::Feature &feature, const std::vector<routeguide::Feature> &features) {
    Process(point, feature, features);
    //finish the RPC - could be call later for running Process asynchronously
    Finish(grpc::Status::OK);
}
void RouteGuideUnaryReactor::OnDone() {
    ABSL_LOG(INFO) << "unary RPC GetFeature completed";
    delete this;
}
void RouteGuideUnaryReactor::OnCancel() {
    ABSL_LOG(ERROR) << "unary RPC GetFeature cancelled";
}
void RouteGuideUnaryReactor::Process(const routeguide::Point &point, routeguide::Feature &feature, const std::vector<routeguide::Feature> &features) {
    feature.set_name(RouteGuideServer::getFeatureName(point, features));
    feature.mutable_location()->CopyFrom(point);
}