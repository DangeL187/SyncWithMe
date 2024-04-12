#include "FileUpdater.hpp"

#include "File/FileHasher.hpp"
#include "Request/Request.hpp"

FileUpdater::FileUpdater() = default;

void FileUpdater::addAllowedFolder(const std::string& folder_path) {
    _allowed_folders.insert(folder_path);
}

void FileUpdater::blockFile(const std::string& file_path, bool value) {
    auto it = _files.find(file_path);
    if (it != _files.end()) {
        it->second.is_blocked = value;
    }
}

void FileUpdater::checkFilesForUpdate(Queue<Request>& requests) {
    for (const std::string& folder_path: _allowed_folders) {
        for (const auto& entry: std::filesystem::recursive_directory_iterator(folder_path)) {
            std::string file_path = entry.path().string();
            std::string hash = FileHasher::calculateHash(file_path);

            std::string local_file_path = file_path;
            local_file_path.erase(0, folder_path.size()+1);
            local_file_path = "../TEMP/" + local_file_path;

            auto it = _files.find(file_path);
            if (it == _files.end()) {
                File file(file_path, hash);
                file.save(local_file_path);
                _files.insert({file_path, file});
            } else {
                if (!it->second.is_blocked && it->second.hash != hash) {
                    requests.add(Request(local_file_path, file_path));
                    it->second.save(local_file_path);
                    it->second.hash = hash;
                }
            }
        }
    }
}