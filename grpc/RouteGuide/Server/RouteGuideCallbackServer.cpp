//
// Created by tuantq3 on 23/07/2024.
//

#include "RouteGuideCallbackServer.h"

#include "Helper.h"
#include "reactor/RouteGuideUnaryReactor.h"
RouteGuideCallbackServer::RouteGuideCallbackServer(const std::string &db) {
    Helper::ParseDB(db, &features_);
}
grpc::ServerUnaryReactor *RouteGuideCallbackServer::GetFeature(grpc::CallbackServerContext *callbackServerContext, const routeguide::Point *point, routeguide::Feature *feature) {
    if (callbackServerContext->IsCancelled()) {
        auto *defaultReactor = callbackServerContext->DefaultReactor();
        defaultReactor->Finish(grpc::Status(grpc::StatusCode::CANCELLED, "Deadline exceeded or Client cancelled, skip this RPC request!!!"));
        return defaultReactor;
    }
    return new RouteGuideUnaryReactor{*point, *feature, features_};
}
grpc::ServerWriteReactor<routeguide::Feature> *RouteGuideCallbackServer::ListFeatures(grpc::CallbackServerContext *callbackServerContext, const routeguide::Rectangle *rectangle) {
    return WithCallbackMethod_GetFeature<WithCallbackMethod_ListFeatures<WithCallbackMethod_RecordRoute<WithCallbackMethod_RouteChat<Service>>>>::ListFeatures(callbackServerContext, rectangle);
}
grpc::ServerReadReactor<routeguide::Point> *RouteGuideCallbackServer::RecordRoute(grpc::CallbackServerContext *callbackServerContext, routeguide::RouteSummary *routeSummary) {
    return WithCallbackMethod_GetFeature<WithCallbackMethod_ListFeatures<WithCallbackMethod_RecordRoute<WithCallbackMethod_RouteChat<Service>>>>::RecordRoute(callbackServerContext, routeSummary);
}
grpc::ServerBidiReactor<routeguide::RouteNote, routeguide::RouteNote> *RouteGuideCallbackServer::RouteChat(grpc::CallbackServerContext *callbackServerContext) {
    return WithCallbackMethod_GetFeature<WithCallbackMethod_ListFeatures<WithCallbackMethod_RecordRoute<WithCallbackMethod_RouteChat<Service>>>>::RouteChat(callbackServerContext);
}