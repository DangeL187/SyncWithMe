#include "FileUpdater.hpp"

#include "File/FileHasher.hpp"
#include "Request/Request.hpp"

FileUpdater::FileUpdater(Queue<Request>* requests): _requests(requests) {
    std::thread thread(&FileUpdater::traverseFiles, this);
    thread.detach();
}

void FileUpdater::addAllowedFolder(const std::string& folder_path) {
    _allowed_folders.insert(folder_path);
}

void FileUpdater::addRequest(const std::string& old_file_path, const std::string& file_path) {
    Request request(old_file_path, file_path);
    _requests->add(request);
    request.toJson();
}

[[noreturn]] void FileUpdater::traverseFiles() {
    while (true) {
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
                        addRequest(local_file_path, file_path);
                        it->second.save(local_file_path);
                        it->second.hash = hash;
                    }
                }
            }
        }
    }
}