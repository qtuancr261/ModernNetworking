//
// Created by tuantq3 on 25/04/2024.
//

#ifndef ROUTGUIDEASYNCSERVER_H
#define ROUTGUIDEASYNCSERVER_H
#include "Helper.h"
#include "gen-cpp/route_guide.grpc.pb.h"


/**
 * @brief gRPC async/non-blocking APIs server
 */
class RoutGuideAsyncServer final {
private:
    class ProcessRequestModel {
    public:

    private:
        // The means of communication with the gRPC runtime for an asynchronous
        // server.
        routeguide::RouteGuide::AsyncService *asyncService_;
        // The producer-consumer queue where for asynchronous server notifications.
        grpc::CompletionQueue *completionQueue_;
        // Context for the rpc, allowing to tweak aspects of it such as the use
        // of compression, authentication, as well as to send metadata back to the
        // client.
        grpc::ServerContext serverContext_;
        //
        routeguide::Point requestPoint_;
        routeguide::Feature responseFeature_;
        grpc::ServerAsyncResponseWriter<routeguide::Feature> responder_;
        // Let's implement a tiny state machine with the following states.
        enum ProcessStatus { CREATE,
                          PROCESS,
                          FINISH };
        ProcessStatus status_;// The current serving state.
    };
};


#endif//ROUTGUIDEASYNCSERVER_H
