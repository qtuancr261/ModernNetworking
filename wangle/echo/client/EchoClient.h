//
// Created by tuantq3 on 24/01/2024.
//
#include "wangle/channel/Handler.h"
#include "wangle/channel/Pipeline.h"
#ifndef SERVER_ECHOCLIENT_H
#define SERVER_ECHOCLIENT_H
using EchoPipeLine = wangle::Pipeline<folly::IOBufQueue&, std::string>;
class EchoHandler : public wangle::HandlerAdapter<std::string> {
public:
    void read(Context *ctx, std::string msg) override;
    void readException(Context *ctx, folly::exception_wrapper e) override;
    void readEOF(Context *ctx) override;
};

class EchoPipeLineFactory : public wangle::PipelineFactory<EchoPipeLine> {
public:
    EchoPipeLine::Ptr newPipeline(std::shared_ptr<folly::AsyncTransport> socket) override;
};

#endif//SERVER_ECHOCLIENT_H
