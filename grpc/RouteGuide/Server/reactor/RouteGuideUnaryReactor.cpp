//
// Created by tuantq3 on 23/07/2024.
//

#include "RouteGuideUnaryReactor.h"
#include "../RouteGuideServer.h"
#include "folly/executors/GlobalExecutor.h"

#include <thread>
RouteGuideUnaryReactor::RouteGuideUnaryReactor(const routeguide::Point &point, routeguide::Feature &feature, const std::vector<routeguide::Feature> &features) {
    // Process(point, feature, features);
    folly::getGlobalCPUExecutor()->add([this, &point, &feature, &features] { Process(point, feature, features); });
    ABSL_LOG(INFO) << "unary RPC GetFeature added to CPU Executor " << std::this_thread::get_id();
    //finish the RPC - could be call later for running Process asynchronously
}
void RouteGuideUnaryReactor::OnDone() {
    ABSL_LOG(INFO) << "unary RPC GetFeature completed";
    delete this;
}
void RouteGuideUnaryReactor::OnCancel() {
    ABSL_LOG(ERROR) << "unary RPC GetFeature cancelled";
}
void RouteGuideUnaryReactor::Process(const routeguide::Point &point, routeguide::Feature &feature, const std::vector<routeguide::Feature> &features) {
    ABSL_LOG(INFO) << "unary RPC GetFeature executing from CPU Executor " << std::this_thread::get_id();
    feature.set_name(RouteGuideServer::getFeatureName(point, features));
    feature.mutable_location()->CopyFrom(point);
    Finish(grpc::Status::OK);
}