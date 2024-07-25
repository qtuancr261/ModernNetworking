//
// Created by tuantq3 on 24/07/2024.
//

#ifndef ROUTEGUIDEWRITEREACTOR_H
#define ROUTEGUIDEWRITEREACTOR_H
#include "../gen-cpp/route_guide.grpc.pb.h"
#include "../gen-cpp/route_guide.pb.h"

/**
 * @brief
 */
class RouteGuideWriteReactor : public grpc::ServerWriteReactor<routeguide::Feature> {
public:
    explicit RouteGuideWriteReactor(const routeguide::Rectangle *rectangle, const std::vector<routeguide::Feature>& features);
    void OnWriteDone(bool isOk) override;
    void OnDone() override;
    void OnCancel() override;
private:
    void ProcessNextWrite();
    //
    const long left_;
    const long right_;
    const long top_;
    const long bottom_;
    const std::vector<routeguide::Feature>& list_features_;
    std::vector<routeguide::Feature>::const_iterator next_feature_iter_;
};


#endif//ROUTEGUIDEWRITEREACTOR_H
