#ifndef CODEWITHME_REQUEST_HPP
#define CODEWITHME_REQUEST_HPP

#include <fstream>
#include <string>

#include "dtl.hpp"

class Request {
public:
    Request(const std::string& old_file_path, const std::string& new_file_path);

    std::string toJson();

private:
    dtl::Diff<std::string, std::vector<std::string>> data;

    void generateData(const std::vector<std::string>& old_contents, const std::vector<std::string>& new_contents);
};

#endif //CODEWITHME_REQUEST_HPP