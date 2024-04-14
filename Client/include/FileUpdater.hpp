#ifndef CODEWITHME_FILEUPDATER_HPP
#define CODEWITHME_FILEUPDATER_HPP

#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "File/File.hpp"
#include "Queue.hpp"
#include "Request/Request.hpp"

class FileUpdater {
public:
    FileUpdater();

    void addAllowedFolder(const std::string& folder_path, const std::string& folder_name); // todo: add interaction with allowed folders - removing, etc.
    void blockFile(const std::string& file_path, bool value);
    void checkFilesForUpdate(Queue<Request>& requests);
    void processRequests(Queue<Request>& requests);

private:
    std::unordered_map<std::string, std::string>        _allowed_folders; // todo: rename to shared
    std::wstring_convert<std::codecvt_utf8<wchar_t>>    _converter;
    std::unordered_map<std::string, File>               _files;

    void removeOrRename(unsigned long long files_amount,
                        const std::pair<const std::basic_string<char>, std::basic_string<char>>&,
                        std::unordered_map<std::string, File>& renamed_files,
                        Queue<Request>& requests);
};

#endif //CODEWITHME_FILEUPDATER_HPP
