//
// Created by tuantq3 on 22/04/2024.
//

#include "RouteGuideClient.h"

#include "Helper.h"

#include <grpcpp/channel.h>
RouteGuideClient::RouteGuideClient(std::shared_ptr<grpc::Channel> channel, const std::string &db) : stub_(routeguide::RouteGuide::NewStub(channel)) {
    Helper::ParseDB(db, &features_);
}
void RouteGuideClient::GetFeature() {
    routeguide::Point point;
    routeguide::Feature feature;
    point = MakePoint(409146138, -746188906);
    GetOneFeature(point, &feature);
    point = MakePoint(0, 0);
    GetOneFeature(point, &feature);
}
routeguide::Point RouteGuideClient::MakePoint(long latitude, long longitude) {
    routeguide::Point point;
    point.set_latitude(latitude);
    point.set_longitude(longitude);
    return point;
}
bool RouteGuideClient::GetOneFeature(const routeguide::Point &point, routeguide::Feature *feature) {
    grpc::ClientContext clientContext;
    grpc::Status status = stub_->GetFeature(&clientContext, point, feature);
    if (!status.ok()) {
        std::cout << "GetFeature rpc failed." << std::endl;
        return false;
    }
    if (!feature->has_location()) {
        std::cout << "Server returns incomplete feature." << std::endl;
        return false;
    }
    if (feature->name().empty()) {
        std::cout << "Found no feature at "
                  << feature->location().latitude() / kCoordFactor_ << ", "
                  << feature->location().longitude() / kCoordFactor_ << std::endl;
    } else {
        std::cout << "Found feature called " << feature->name() << " at "
                  << feature->location().latitude() / kCoordFactor_ << ", "
                  << feature->location().longitude() / kCoordFactor_ << std::endl;
    }
    return true;
    return true;
}