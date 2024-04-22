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
    std::string db_content(db);
    db_content.erase(
            std::remove_if(db_content.begin(), db_content.end(), isspace),
            db_content.end());

    Parser parser(db_content);
    routeguide::Feature feature;
    while (!parser.Finished()) {
        featuresList->push_back(routeguide::Feature());
        if (!parser.TryParseOne(&featuresList->back())) {
            std::cout << "Error parsing the db file";
            featuresList->clear();
            break;
        }
    }
    std::cout << "DB parsed, loaded " << featuresList->size() << " features."
              << std::endl;
}


Helper::Parser::Parser(const std::string &db) : db_{db} {
    // remove all spaces.
    db_.erase(std::remove_if(db_.begin(), db_.end(), isspace), db_.end());
    if (!Match("[")) {
        SetFailedAndReturnFalse();
    }
}
bool Helper::Parser::Finished() {
    return current_ >= db_.size();
}
bool Helper::Parser::TryParseOne(routeguide::Feature *feature) {
    if (failed_ || Finished() || !Match("{")) {
        return SetFailedAndReturnFalse();
    }
    if (!Match(location_) || !Match("{") || !Match(latitude_)) {
        return SetFailedAndReturnFalse();
    }

    long temp = 0;
    ReadLong(&temp);
    feature->mutable_location()->set_latitude(temp);
    if (!Match(",") || !Match(longitude_)) {
        return SetFailedAndReturnFalse();
    }
    ReadLong(&temp);
    feature->mutable_location()->set_longitude(temp);
    if (!Match("},") || !Match(name_) || !Match("\"")) {
        return SetFailedAndReturnFalse();
    }
    size_t name_start = current_;
    while (current_ != db_.size() && db_[current_++] != '"') {
    }
    if (current_ == db_.size()) {
        return SetFailedAndReturnFalse();
    }
    feature->set_name(db_.substr(name_start, current_ - name_start - 1));
    if (!Match("},")) {
        if (db_[current_ - 1] == ']' && current_ == db_.size()) {
            return true;
        }
        return SetFailedAndReturnFalse();
    }
    return true;
}
bool Helper::Parser::Match(const std::string &prefix) {
    bool isEqual = db_.substr(current_, prefix.size()) == prefix;
    current_ += prefix.size();
    return isEqual;
}
bool Helper::Parser::SetFailedAndReturnFalse() {
    failed_ = true;
    return false;
}
void Helper::Parser::ReadLong(long *l) {
    size_t start = current_;
    while (current_ != db_.size() && db_[current_] != ',' &&
           db_[current_] != '}') {
        current_++;
    }
    // It will throw an exception if fails.
    *l = std::stol(db_.substr(start, current_ - start));
}