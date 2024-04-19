#ifndef CODEWITHME_FILEUPDATER_HPP
#define CODEWITHME_FILEUPDATER_HPP

#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "File/File.hpp"
#include "File/FileHasher.hpp"
#include "Response/Response.hpp"
#include "Request/Request.hpp"
#include "Queue.hpp"

class FileUpdater {
public:
    FileUpdater();

    void addSharedFolder(const std::string& folder_name, const std::string& folder_path); // todo: add interaction with allowed folders - removing, etc.
    void checkFilesForUpdate(Queue<Request>& requests);
    void processResponses(Queue<Response>& responses);

private:
    std::wstring_convert<std::codecvt_utf8<wchar_t>>    _converter;
    std::unordered_map<std::string, File>               _files;
    std::string                                         _main_folder;
    std::unordered_map<std::string, std::string>        _shared_folders;

    void removeOrRename(unsigned long long files_amount,
                        const std::pair<const std::basic_string<char>, std::basic_string<char>>&,
                        std::unordered_map<std::string, File>& renamed_files,
                        Queue<Request>& requests);
};

#endif //CODEWITHME_FILEUPDATER_HPP
