#ifndef CODEWITHME_FILEUPDATER_HPP
#define CODEWITHME_FILEUPDATER_HPP

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "File/File.hpp"
#include "Queue.hpp"
#include "Request/Request.hpp"

class FileUpdater {
public:
    FileUpdater();

    void addAllowedFolder(const std::string& folder_path); // todo: add interaction with allowed folders - removing, etc.
    void blockFile(const std::string& file_path, bool value);
    void checkFilesForUpdate(Queue<Request>& requests);
    void processRequests(Queue<Request>& requests); // #async

private:
    std::unordered_set<std::string>         _allowed_folders;
    std::unordered_map<std::string, File>   _files;
};

#endif //CODEWITHME_FILEUPDATER_HPP
