//
// Created by tuantq3 on 26/07/2024.
//

#ifndef ROUTEGUIDEREADREACTOR_H
#define ROUTEGUIDEREADREACTOR_H

#include "../gen-cpp/route_guide.grpc.pb.h"
#include "../gen-cpp/route_guide.pb.h"

/**
 * @brief This reactor is similar to ServerWriteReactor
 */
class RouteGuideReadReactor final : public grpc::ServerReadReactor<routeguide::Point> {
public:
    explicit RouteGuideReadReactor(const std::vector<routeguide::Feature>& features, routeguide::RouteSummary& routeSummary);
    void OnReadDone(bool isOk) override;
    void OnDone() override;
    void OnCancel() override;
private:
    std::chrono::system_clock::time_point start_time_;
    const std::vector<routeguide::Feature>& features_;
    routeguide::RouteSummary& summary_;
    routeguide::Point currentPoint_;
    routeguide::Point prevPoint_;
    int countReadPoint_{0};
    int countMatchFeature_{0};
    float distance_{0.0f};
};


#endif//ROUTEGUIDEREADREACTOR_H
