//
// Created by tuantq on 17/04/2024.
//

#include "Helper.h"
#include "gen-cpp/route_guide.grpc.pb.h"
#include <fstream>
#include <iostream>
#include <sstream>
std::string Helper::GetDbFileContent(int argc, char *argv[]) {
    std::string db_path;
    std::string arg_str{"--db_path"};
    if (argc > 1) {
        std::string argv_1 = argv[1];
        size_t start_position = argv_1.find(arg_str);
        if (start_position != std::string::npos) {
            start_position += arg_str.size();
            if (argv_1[start_position] == ' ' || argv_1[start_position] == '=') {
                db_path = argv_1.substr(start_position + 1);
            }
        }
    } else {
        db_path = "../route_guide_db.json";
    }
    // let's read the db file route location
    std::ifstream db_file{db_path};
    if (!db_file.is_open()) {
        std::cout << "Failed to open " << db_path << std::endl;
        abort();
    }
    std::stringstream dbreadStream;
    dbreadStream << db_file.rdbuf();
    return dbreadStream.str();
}
void Helper::ParseDB(const std::string &db, std::vector<routeguide::Feature> *featuresList) {
    featuresList->clear();
}

Helper::Parser::Parser(const std::string &db) : db_{db} {
    // remove all spaces.
    db_.erase(std::remove_if(db_.begin(), db_.end(), isspace), db_.end());
}
bool Helper::Parser::Match(const std::string &prefix) {
    bool isEqual = db_.substr(current_, prefix.size()) == prefix;
    current_ += prefix.size();
    return false;
}
bool Helper::Parser::SetFailedAndReturnFalse() {
    failed_ = true;
    return false;
}