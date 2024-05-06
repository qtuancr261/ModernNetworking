//
// Created by tuantq3 on 25/04/2024.
//

#include "RoutGuideAsyncServer.h"

#include "RouteGuideServer.h"

#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
RoutGuideAsyncServer::RoutGuideAsyncServer(std::string db) {
    Helper::ParseDB(db, &features_);
}
RoutGuideAsyncServer::~RoutGuideAsyncServer() {
    if (server_ != nullptr) {
        server_->Shutdown();
    }
    if (completionQueue_ != nullptr) {
        completionQueue_->Shutdown();
    }
}
void RoutGuideAsyncServer::Run() {
    std::string server_address{"0.0.0.0:1943"};
    grpc::ServerBuilder serverBuilder;
    serverBuilder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service_" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *asynchronous* service.
    serverBuilder.RegisterService(&asyncService_);
    // Get hold of the completion queue used for the asynchronous communication
    // with the gRPC runtime.
    completionQueue_ = serverBuilder.AddCompletionQueue();
    server_ = serverBuilder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;
    // Proceed to the server's main loop
    HandleRPCCalls();
}
void RoutGuideAsyncServer::HandleRPCCalls() {
    // spawn new model instance to handle new clients
    new ProcessRequestModel(&asyncService_, completionQueue_.get(), &features_);
    void* reqTag;
    bool isOk;
    while (true) {
        // Block waiting to read the next event from the completion queue. The
        // event is uniquely identified by its tag, which in this case is the
        // memory address of a ProcessRequestModel instance.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or cq_ is shutting down.
        std::cout << "Waiting for completion queue" << std::endl;
        GPR_ASSERT(completionQueue_->Next(&reqTag, &isOk));
        GPR_ASSERT(isOk);
        static_cast<ProcessRequestModel*>(reqTag)->Proceed();
    }
}
RoutGuideAsyncServer::ProcessRequestModel::ProcessRequestModel(routeguide::RouteGuide::AsyncService *service, grpc::ServerCompletionQueue *serverCompletionQueue, const std::vector<routeguide::Feature>* features)
    : asyncService_{service}, comQueue_{serverCompletionQueue}, features_(features), responder_{&serverContext_}, status_{CREATE} {
    // Invoke the serving logic right away.
    Proceed();
}
void RoutGuideAsyncServer::ProcessRequestModel::Proceed() {
    std::cout << "Processing request asynchronous" << std::endl;
    if (status_ == CREATE) {
        // make this instance progress to the PROCESS state
        status_ = PROCESS;
        // just handle one API service :V
        asyncService_->RequestGetFeature(&serverContext_, &requestPoint_, &responder_, comQueue_, comQueue_, this);
    } else if (status_ == PROCESS) {
        // Spawn a new CallData instance to serve new clients while we process
        // the one for this CallData. The instance will deallocate itself as
        // part of its FINISH state.
        new ProcessRequestModel(asyncService_, comQueue_, features_);
        // the actual processing flow
        responseFeature_.set_name(RouteGuideServer::getFeatureName(requestPoint_, *features_));
        responseFeature_.mutable_location()->CopyFrom(requestPoint_);
        // And we are done! Let the gRPC runtime know we've finished, using the
        // memory address of this instance as the uniquely identifying tag for
        // the event.
        status_ = FINISH;
        responder_.Finish(responseFeature_, grpc::Status::OK, this);
    } else {
        GPR_ASSERT(status_ == FINISH);
        // Once in the FINISH state, deallocate ourselves
        delete this;
    }
}