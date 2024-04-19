#ifndef CODEWITHME_RESPONSE_HPP
#define CODEWITHME_RESPONSE_HPP

#include <fstream>
#include <string>
#include <unordered_map>

#include "json.hpp"

class Response {
public:
    std::unordered_map<std::string, std::string>    changes;
    bool                                            deleted;
    std::string                                     file;
    std::string                                     new_file_name;

    explicit Response(const std::string& json);
};

#endif //CODEWITHME_RESPONSE_HPP
