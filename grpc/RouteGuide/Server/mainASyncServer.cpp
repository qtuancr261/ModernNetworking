//
// Created by tuantq3 on 06/05/2024.
//
#include "RoutGuideAsyncServer.h"
int main(int argc, char* argv[]) {
    std::string db = Helper::GetDbFileContent(argc, argv);
    RoutGuideAsyncServer async_server{db};
    async_server.Run();
}