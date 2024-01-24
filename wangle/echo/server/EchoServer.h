//
// Created by tuantq3 on 23/01/2024.
//

#ifndef SERVER_ECHOSERVER_H
#define SERVER_ECHOSERVER_H
#include "folly/portability/GFlags.h"
#include "wangle/channel/AsyncSocketHandler.h"
#include "wangle/codec/LineBasedFrameDecoder.h"
#include "wangle/codec/StringCodec.h"
using EchoPipeLine = wangle::Pipeline<folly::IOBufQueue&, std::string>;
/**
 * Receive a string and write it back straight
 */
class EchoHandler : public wangle::HandlerAdapter<std::string> {
public:
    void read(Context *ctx, std::string msg) override;
};

/*
 * Chain the handlers together to define the response pipeline
 */
class EchoPipeLineFactory : public wangle::PipelineFactory<EchoPipeLine> {
public:
    EchoPipeLine ::Ptr newPipeline(std::shared_ptr<folly::AsyncTransport> socket) override;
};


#endif//SERVER_ECHOSERVER_H
