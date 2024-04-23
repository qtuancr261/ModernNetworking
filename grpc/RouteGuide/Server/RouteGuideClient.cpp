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
void RouteGuideClient::ListFeatures() {
    routeguide::Rectangle rect;
    routeguide::Feature feature;
    grpc::ClientContext context;

    rect.mutable_lo()->set_latitude(400000000);
    rect.mutable_lo()->set_longitude(-750000000);
    rect.mutable_hi()->set_latitude(420000000);
    rect.mutable_hi()->set_longitude(-730000000);

    std::cout << "Looking for features between 40, -75 and 42, -73"
              << std::endl;

    std::unique_ptr<grpc::ClientReader<routeguide::Feature> > reader(
        stub_->ListFeatures(&context, rect));
    while (reader->Read(&feature)) {
        std::cout << "Found feature called " << feature.name() << " at "
                  << feature.location().latitude() / kCoordFactor_ << ", "
                  << feature.location().longitude() / kCoordFactor_ << std::endl;
    }
    grpc::Status status = reader->Finish();
    if (status.ok()) {
        std::cout << "ListFeatures rpc succeeded." << std::endl;
    } else {
        std::cout << "ListFeatures rpc failed." << std::endl;
    }
}
routeguide::Point RouteGuideClient::MakePoint(long latitude, long longitude) {
    routeguide::Point point;
    point.set_latitude(latitude);
    point.set_longitude(longitude);
    return point;
}
routeguide::Feature RouteGuideClient::MakeFeature(const std::string &name, long latitude, long longitude) {
    routeguide::Feature f;
    f.set_name(name);
    f.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
    return f;
}
routeguide::RouteNote RouteGuideClient::MakeRouteNote(const std::string &message, long latitude, long longitude) {
    routeguide::RouteNote n;
    n.set_message(message);
    n.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
    return n;
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
}