//
// Created by tuantq3 on 23/01/2024.
//

#include "EchoServer.h"
DEFINE_uint32(lineMaxLength, 8192, "LineBaseFrameDecoder max length");
void EchoHandler::read(wangle::HandlerAdapter<std::string>::Context *ctx, std::string msg) {
    LOG(INFO) << "read " << msg;
    write(ctx, msg.append("\r\n"));
}
EchoPipeLine ::Ptr EchoPipeLineFactory::newPipeline(std::shared_ptr<folly::AsyncTransport> socket) {
    auto pipeLine = EchoPipeLine::create();
    pipeLine->addBack(wangle::AsyncSocketHandler(socket));
    pipeLine->addBack(wangle::LineBasedFrameDecoder(FLAGS_lineMaxLength));
    pipeLine->addBack(wangle::StringCodec());
    pipeLine->addBack(EchoHandler());
    pipeLine->finalize();
    return pipeLine;
}
