//
// Created by tuantq3 on 24/01/2024.
//

#include "EchoClient.h"
#include <string>
#include "wangle/channel/AsyncSocketHandler.h"
#include "wangle/channel/EventBaseHandler.h"
#include "wangle/codec/LineBasedFrameDecoder.h"
#include "wangle/codec/StringCodec.h"

void EchoHandler::read(Context *ctx, std::string msg) {
//    LOG(INFO) << "Received back: " << msg;
}
void EchoHandler::readException(wangle::Handler<std::string>::Context *ctx, folly::exception_wrapper e) {
//    LOG(ERROR) << "Read exeption: " << folly::exceptionStr(e);
    Handler::close(ctx);
}
void EchoHandler::readEOF(wangle::Handler<std::string>::Context *ctx) {
//    LOG(ERROR) << "Read eof: ";
    Handler::readEOF(ctx);
}
EchoPipeLine::Ptr EchoPipeLineFactory::newPipeline(std::shared_ptr<folly::AsyncTransport> socket) {
    auto pipeLine = EchoPipeLine ::create();
    pipeLine->addBack(wangle::AsyncSocketHandler(socket));
    // different from Server Factory
    // make sure we can write from any thread
    pipeLine->addBack(wangle::EventBaseHandler());
    pipeLine->addBack(wangle::LineBasedFrameDecoder(8192, false));
    pipeLine->addBack(wangle::StringCodec());
    pipeLine->addBack(EchoHandler());
    pipeLine->finalize();
    return pipeLine;
}
