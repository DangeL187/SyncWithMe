#ifndef CODEWITHME_REQUEST_HPP
#define CODEWITHME_REQUEST_HPP

#include <fstream>
#include <string>

#include "dtl.hpp"
#include "json.hpp"

class Request {
public:
    Request();
    Request(const std::string& shared_file_path, const std::string& old_file_path, const std::string& new_file_path);
    Request(const std::string& shared_file_path, const std::string& new_file_name);
    Request(const std::string& shared_file_path, bool is_deleted);

    std::string toJson();

    [[nodiscard]] bool isValid() const;

private:
    dtl::Diff<std::string, std::vector<std::string>>    _data;
    std::string                                         _file_path;
    bool                                                _is_deleted = false;
    bool                                                _is_valid = true;
    std::string                                         _new_file_name;

    void generateData(const std::vector<std::string>& old_contents, const std::vector<std::string>& new_contents);
};

#endif //CODEWITHME_REQUEST_HPP
