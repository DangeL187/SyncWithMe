#ifndef CODEWITHME_FILEUPDATER_HPP
#define CODEWITHME_FILEUPDATER_HPP

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "File/File.hpp"
#include "Queue.hpp"
#include "Request/Request.hpp"

class FileUpdater {
public:
    explicit FileUpdater(Queue<Request>* requests);

    void addAllowedFolder(const std::string& folder_path);
    // todo: add interaction with allowed folders - removing, etc.

private:
    std::unordered_set<std::string>         _allowed_folders;
    std::unordered_map<std::string, File>   _files;
    Queue<Request>*                         _requests;

    void addRequest(const std::string& old_file_path, const std::string& file_path);
    [[noreturn]] void traverseFiles();
};

#endif //CODEWITHME_FILEUPDATER_HPP
