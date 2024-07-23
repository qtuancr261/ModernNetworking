//
// Created by tuantq3 on 23/07/2024.
//

#ifndef ROUTEGUIDEUNARYREACTOR_H
#define ROUTEGUIDEUNARYREACTOR_H

#include "../gen-cpp/route_guide.pb.h"
#include "../gen-cpp/route_guide.grpc.pb.h"
/**
 * @brief
 */
class RouteGuideUnaryReactor final : public grpc::ServerUnaryReactor {
public:
    RouteGuideUnaryReactor(const routeguide::Point& point, routeguide::Feature& feature, const std::vector<routeguide::Feature>& features);
    void OnDone() override;
    void OnCancel() override;
private:
    /**
     * @brief 
     * @param point 
     * @param feature
     * @param features 
     */
    void Process(const routeguide::Point& point, routeguide::Feature& feature, const std::vector<routeguide::Feature>& features);
};



#endif //ROUTEGUIDEUNARYREACTOR_H
