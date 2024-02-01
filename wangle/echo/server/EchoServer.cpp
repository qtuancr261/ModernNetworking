//
// Created by tuantq3 on 23/01/2024.
//

#include "EchoServer.h"
#include <iostream>
DEFINE_uint32(lineMaxLength, 8192, "LineBaseFrameDecoder max length");
void EchoHandler::read(wangle::HandlerAdapter<std::string>::Context *ctx, std::string msg) {
    std::cout << "handling " << msg << std::endl;
    write(ctx, msg.append("\r\n"));
}
EchoPipeLine ::Ptr EchoPipeLineFactory::newPipeline(std::shared_ptr<folly::AsyncTransport> socket) {
    std::cout << "new pipeline on thread " << std::this_thread::get_id() << std::endl;
    auto pipeLine = EchoPipeLine::create();
    pipeLine->addBack(wangle::AsyncSocketHandler(socket));
    pipeLine->addBack(wangle::LineBasedFrameDecoder(FLAGS_lineMaxLength));
    pipeLine->addBack(wangle::StringCodec());
    pipeLine->addBack(EchoHandler());
    pipeLine->finalize();
    return pipeLine;
}
