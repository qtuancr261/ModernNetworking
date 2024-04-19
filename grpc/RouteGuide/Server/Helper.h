//
// Created by tuantq on 17/04/2024.
//

#ifndef HELPER_H
#define HELPER_H
#include <string>
#include <vector>
namespace routeguide {
    class Feature;

}
class Helper {
public:
    static std::string GetDbFileContent(int argc, char *argv[]);
    static void ParseDB(const std::string &db, std::vector<routeguide::Feature> *featuresList);

public:
    class Parser {
    public:
        explicit Parser(const std::string &db);
        bool Finished();
        bool TryParseOne(routeguide::Feature* feature);
    private:
        bool Match(const std::string& prefix);
        bool SetFailedAndReturnFalse();
        void ReadLong(long* l);
    private:
        bool failed_ = false;
        std::string db_;
        size_t current_ = 0;
        const std::string location_{"\"location\":"};
        const std::string latitude_{"\"latitude\":"};
        const std::string longitude_{"\"longitude\":"};
        const std::string name_{"\"name\":"};
    };
};


#endif//HELPER_H
