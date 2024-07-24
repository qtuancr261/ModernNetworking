//
// Created by tuantq3 on 23/07/2024.
//

#ifndef ROUTEGUIDEUNARYREACTOR_H
#define ROUTEGUIDEUNARYREACTOR_H

#include "../gen-cpp/route_guide.pb.h"
#include "../gen-cpp/route_guide.grpc.pb.h"
/**
 * @brief all the overriable callbacks within the reactor should be fast. It could
 * impact other RPCs within the process
 */
class RouteGuideUnaryReactor final : public grpc::ServerUnaryReactor {
public:
    RouteGuideUnaryReactor(const routeguide::Point& point, routeguide::Feature& feature, const std::vector<routeguide::Feature>& features);
    /**
     * @brief supposed to return quickly. Never perform blocking work (I/O event) in such callbacks
     */
    void OnDone() override;
    /**
     * @brief
     */
    void OnCancel() override;
private:
    /**
     * @brief this function could be process from the same thread as the constructor or in another thread (asynchronous) if needed
     * @param point 
     * @param feature
     * @param features - list of all features we preload from our database
     */
    void Process(const routeguide::Point& point, routeguide::Feature& feature, const std::vector<routeguide::Feature>& features);
};



#endif //ROUTEGUIDEUNARYREACTOR_H
