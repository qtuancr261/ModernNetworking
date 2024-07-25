//
// Created by tuantq3 on 24/07/2024.
//

#include "RouteGuideWriteReactor.h"

#include <thread>
RouteGuideWriteReactor::RouteGuideWriteReactor(const routeguide::Rectangle *rectangle,
                                               const std::vector<routeguide::Feature>& features) : left_((std::min)(rectangle->lo().longitude(),
                                                                                                                   rectangle->hi().longitude())),
                                                                                                  right_((std::max)(rectangle->lo().longitude(),
                                                                                                                    rectangle->hi().longitude())),
                                                                                                  top_((std::max)(rectangle->lo().latitude(),
                                                                                                                  rectangle->hi().latitude())),
                                                                                                  bottom_((std::min)(rectangle->lo().latitude(),
                                                                                                                     rectangle->hi().latitude())),
                                                                                                  list_features_{features}, next_feature_iter_{features.cbegin()} {
    ABSL_LOG(INFO) << " init write action " << std::this_thread::get_id();
    ProcessNextWrite();
}
void RouteGuideWriteReactor::OnWriteDone(bool isOk) {
    if (!isOk) {
        Finish(grpc::Status(grpc::StatusCode::UNKNOWN, " Unexpected failure when write stream"));
    }
    ABSL_LOG(INFO) << " done write action - next action " << std::this_thread::get_id();
    ProcessNextWrite();
}
void RouteGuideWriteReactor::OnDone() {
    ABSL_LOG(INFO) << " done done action " << std::this_thread::get_id();
    delete this;
}
void RouteGuideWriteReactor::OnCancel() {
    ABSL_LOG(ERROR) << "RPC write Cancelled";
}
void RouteGuideWriteReactor::ProcessNextWrite() {
    while (next_feature_iter_ != list_features_.cend()) {
        const routeguide::Feature &current_feature{*next_feature_iter_};
        ++next_feature_iter_;
        if (current_feature.location().longitude() >= left_ &&
            current_feature.location().longitude() <= right_ &&
            current_feature.location().latitude() >= bottom_ &&
            current_feature.location().latitude() <= top_) {
            StartWrite(&current_feature);
            return;
        }
    }
    // nothing to write - just finish
    Finish(grpc::Status::OK);
}