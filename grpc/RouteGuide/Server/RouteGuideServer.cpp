//
// Created by tuantq3 on 16/04/2024.
//

#include "RouteGuideServer.h"
#include "Helper.h"
RouteGuideServer::RouteGuideServer(const std::string &db) {
    Helper::ParseDB(db, &features_);
}
grpc::Status RouteGuideServer::GetFeature(grpc::ServerContext *context, const routeguide::Point *request, routeguide::Feature *response) {
    // return Service::GetFeature(context, request, response);
    response->set_name(getFeatureName(*request, features_));
    response->mutable_location()->CopyFrom(*request);
    return grpc::Status::OK;
}
grpc::Status RouteGuideServer::ListFeatures(grpc::ServerContext *context, const routeguide::Rectangle *request, grpc::ServerWriter<routeguide::Feature> *writer) {
    // return Service::ListFeatures(context, request, writer);
    auto lo = request->lo();
    auto hi = request->hi();
    long left = (std::min)(lo.longitude(), hi.longitude());
    long right = (std::max)(lo.longitude(), hi.longitude());
    long top = (std::max)(lo.latitude(), hi.latitude());
    long bottom = (std::min)(lo.latitude(), hi.latitude());
    for (const routeguide::Feature& f : features_) {
        if (f.location().longitude() >= left &&
            f.location().longitude() <= right &&
            f.location().latitude() >= bottom && f.location().latitude() <= top) {
            writer->Write(f);
            }
    }
    return grpc::Status::OK;
}
grpc::Status RouteGuideServer::RecordRoute(grpc::ServerContext *context, grpc::ServerReader<routeguide::Point> *reader, routeguide::RouteSummary *response) {
    return Service::RecordRoute(context, reader, response);
}
grpc::Status RouteGuideServer::RouteChat(grpc::ServerContext *context, grpc::ServerReaderWriter<routeguide::RouteNote, routeguide::RouteNote> *stream) {
    return Service::RouteChat(context, stream);
}
float RouteGuideServer::convertToRadians(float num) {
    return num * 3.1415926 / 180;
    ;
}
float RouteGuideServer::getDistance(const routeguide::Point &start, const routeguide::Point &end) {
    const float kCoordFactor = 10000000.0;
    float lat_1 = start.latitude() / kCoordFactor;
    float lat_2 = end.latitude() / kCoordFactor;
    float lon_1 = start.longitude() / kCoordFactor;
    float lon_2 = end.longitude() / kCoordFactor;
    float lat_rad_1 = RouteGuideServer::convertToRadians(lat_1);
    float lat_rad_2 = RouteGuideServer::convertToRadians(lat_2);
    float delta_lat_rad = RouteGuideServer::convertToRadians(lat_2 - lat_1);
    float delta_lon_rad = RouteGuideServer::convertToRadians(lon_2 - lon_1);

    float a = pow(sin(delta_lat_rad / 2), 2) +
              cos(lat_rad_1) * cos(lat_rad_2) * pow(sin(delta_lon_rad / 2), 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    int R = 6371000;// metres

    return R * c;
}
std::string RouteGuideServer::getFeatureName(const routeguide::Point &point, const std::vector<routeguide::Feature> &feature_list) {
    for (const routeguide::Feature &f: feature_list) {
        if (f.location().latitude() == point.latitude() &&
            f.location().longitude() == point.longitude()) {
            return f.name();
        }
    }
    return "";
}