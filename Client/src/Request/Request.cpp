#include "Request/Request.hpp"

Request::Request() {
    _is_valid = false;
}

Request::Request(const std::string& shared_file_path, const std::string& new_file_name) {
    _file_path = shared_file_path;
    _new_file_name = new_file_name;
}

Request::Request(const std::string& shared_file_path, bool is_deleted) {
    _file_path = shared_file_path;
    _is_deleted = is_deleted;
}

Request::Request(const std::string& shared_file_path, const std::string& old_file_path, const std::string& new_file_path) {
    _file_path = shared_file_path;

    std::ifstream old_file(std::filesystem::path(old_file_path).c_str());
    std::ifstream new_file(std::filesystem::path(new_file_path).c_str());
    std::vector<std::string> old_contents;
    std::vector<std::string> new_contents;

    if (old_file.is_open()) {
        std::string line;
        while (std::getline(old_file, line)) {
            old_contents.push_back(line);
        }
        old_file.close();
    }

    if (new_file.is_open()) {
        std::string line;
        while (std::getline(new_file, line)) {
            new_contents.push_back(line);
        }
        new_file.close();
    }

    generateData(old_contents, new_contents);
}

void Request::generateData(const std::vector<std::string>& old_contents, const std::vector<std::string>& new_contents) {
    _data = dtl::Diff<std::string, std::vector<std::string>>(old_contents, new_contents);
    _data.compose();
}

bool Request::isValid() const {
    return _is_valid;
}

std::string Request::toJson() {
    nlohmann::json request;
    nlohmann::json changes;

    request["file"] = _file_path;
    request["deleted"] = int(_is_deleted);
    request["new_file_name"] = _new_file_name;

    for (auto& i: _data.getSes().getSequence()) {
        nlohmann::json change;
        change["type"] = i.second.type;
        if (i.second.type == 1) change["line"] = i.second.afterIdx;
        else if (i.second.type == -1) change["line"] = i.second.beforeIdx;
        else continue;
        change["content"] = i.first;

        changes.push_back(change);
    }

    request["changes"] = changes;

    return request.dump();
}