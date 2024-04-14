#include "FileUpdater.hpp"

#include "File/FileHasher.hpp"
#include "Request/Request.hpp"

FileUpdater::FileUpdater() {
    if (!std::filesystem::exists("../TEMP")) {
        std::filesystem::create_directory("../TEMP");
    }
}

void FileUpdater::addAllowedFolder(const std::string& folder_path, const std::string& folder_name) {
    _allowed_folders.insert({folder_path, folder_name});
}

void FileUpdater::blockFile(const std::string& file_path, bool value) {
    auto it = _files.find(file_path);
    if (it != _files.end()) {
        it->second.is_blocked = value;
    }
}

void FileUpdater::checkFilesForUpdate(Queue<Request>& requests) {
    for (const auto& shared_folder: _allowed_folders) {
        unsigned long long files_amount = 0;
        std::unordered_map<std::string, File> renamed_files;
        for (const auto& entry: std::filesystem::recursive_directory_iterator(shared_folder.first)) {
            std::wstring w_full_file_path = entry.path().wstring();
            std::string full_file_path = _converter.to_bytes(w_full_file_path);

            std::string local_file_path;
            std::string shared_file_path;
            std::string hash = FileHasher::hash(w_full_file_path);

            local_file_path = full_file_path;
            local_file_path.erase(0, shared_folder.first.size()+1);
            shared_file_path = shared_folder.second + "/" + local_file_path;
            local_file_path = "../TEMP/" + shared_file_path;

            auto it = _files.find(full_file_path);
            if (it == _files.end()) {
                File file(full_file_path, hash);
                file.save(local_file_path);

                for (auto& i: _files) {
                    if (i.second.hash == hash) {
                        renamed_files.insert({hash, file});
                    }
                }

                _files.insert({full_file_path, file});
            }
            else if (!it->second.is_blocked && !hash.empty() && it->second.hash != hash) {
                std::cout << shared_file_path << " - this file is in the _files and was changed\n"; // todo: delete
                requests.add(Request(shared_file_path, local_file_path, full_file_path));
                it->second.save(local_file_path);
                it->second.hash = hash;
            }
            files_amount++;
        }
        removeOrRename(files_amount, shared_folder, renamed_files, requests);
    }
}

void FileUpdater::processRequests(Queue<Request>& requests) {
    while (!requests.isEmpty()) {
        //std::cout << "processing request from server\n";
        std::cout << requests.get().toJson() << " #\n";
        //std::cout << "end of processing\n\n";
    }
}

void FileUpdater::removeOrRename(unsigned long long files_amount,
                                 const std::pair<const std::basic_string<char>, std::basic_string<char>>& shared_folder,
                                 std::unordered_map<std::string, File>& renamed_files,
                                 Queue<Request>& requests)
{
    if (files_amount < _files.size()) {
        for (auto& file: _files) {
            try {
                if (!file.first.empty() && !std::filesystem::exists(file.first)) {
                    std::string local_file_path = file.first;
                    std::string shared_file_path;

                    local_file_path.erase(0, shared_folder.first.size()+1);
                    shared_file_path = shared_folder.second + "/" + local_file_path;
                    local_file_path = "../TEMP/" + shared_file_path;

                    auto renamed_file = renamed_files.find(file.second.hash);
                    if (renamed_file != _files.end()) {
                        std::string renamed_file_path = renamed_file->second.name;
                        std::replace(renamed_file_path.begin(), renamed_file_path.end(), '\\', '/');

                        std::string local_renamed_file_path = renamed_file_path;
                        std::string shared_renamed_file_path;
                        local_renamed_file_path.erase(0, shared_folder.first.size()+1);
                        shared_renamed_file_path = shared_folder.second + "/" + local_renamed_file_path;
                        local_renamed_file_path = "../TEMP/" + shared_renamed_file_path;

                        std::filesystem::rename(local_file_path, local_renamed_file_path);
                        requests.add(Request(shared_file_path, shared_renamed_file_path));
                        std::cout << renamed_file_path << " - this file was renamed\n";
                    } else {
                        std::filesystem::remove(local_file_path);
                        requests.add(Request(shared_file_path, true));
                        std::cout << local_file_path << " was deleted\n"; // todo: delete
                    }

                    _files.erase(file.first);
                    files_amount--;
                }
            } catch (std::exception& e) {}
            if (files_amount == _files.size()) break;
        }
    }
}