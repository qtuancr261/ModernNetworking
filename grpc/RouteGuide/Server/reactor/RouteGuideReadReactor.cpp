//
// Created by tuantq3 on 26/07/2024.
//

#include "RouteGuideReadReactor.h"

#include "../RouteGuideServer.h"
RouteGuideReadReactor::RouteGuideReadReactor(const std::vector<routeguide::Feature> &features, routeguide::RouteSummary &routeSummary)
    : start_time_{std::chrono::system_clock::now()},
      features_{features},
      summary_{routeSummary} {
    StartRead(&currentPoint_);
}
void RouteGuideReadReactor::OnReadDone(bool isOK) {
    if (isOK) {
        ++countReadPoint_;
        if (RouteGuideServer::getFeatureName(currentPoint_, features_).empty()) {
            ++countMatchFeature_;
        }
        if (countReadPoint_ > 1) {
            distance_ += RouteGuideServer::getDistance(prevPoint_, currentPoint_);
        }
        prevPoint_ = currentPoint_;
        StartRead(&currentPoint_);
    } else {
        // finish reading - collect summary and send it back to client
        summary_.set_point_count(countReadPoint_);
        summary_.set_feature_count(countMatchFeature_);
        summary_.set_distance(distance_);
        auto secs = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now() - start_time_);
        summary_.set_elapsed_time(secs.count());
        Finish(grpc::Status::OK);
    }
}
void RouteGuideReadReactor::OnDone() {
    ABSL_LOG(INFO) << "done all read action";
    delete this;
}
void RouteGuideReadReactor::OnCancel() {
    ABSL_LOG(ERROR) << "read cancel ";
}