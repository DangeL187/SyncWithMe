#include "FileUpdater.hpp"

FileUpdater::FileUpdater() {
    if (!std::filesystem::exists("../TEMP")) {
        std::filesystem::create_directory("../TEMP");
    }
}

void FileUpdater::addSharedFolder(const std::string& folder_name, const std::string& folder_path) {
    if (!std::filesystem::exists(folder_path)) {
        std::filesystem::create_directory(folder_path);
    }
    _shared_folders.insert({folder_name, folder_path});
}

void FileUpdater::checkFilesForUpdate(Queue<Request>& requests) {
    for (const auto& shared_folder: _shared_folders) {
        unsigned long long files_amount = 0;
        std::unordered_map<std::string, File> renamed_files;
        for (const auto& entry: std::filesystem::recursive_directory_iterator(shared_folder.second)) {
            std::wstring w_full_file_path = entry.path().wstring();
            std::string full_file_path = _converter.to_bytes(w_full_file_path);

            std::string local_file_path;
            std::string shared_file_path;
            std::string hash = FileHasher::hash(w_full_file_path);

            local_file_path = full_file_path;
            local_file_path.erase(0, shared_folder.second.size()+1);
            shared_file_path = shared_folder.first + "/" + local_file_path;
            local_file_path = "../TEMP/" + shared_file_path;

            File& file = _files[shared_file_path];

            if (!file.isValid()) {
                File new_file(full_file_path, hash);
                new_file.save(local_file_path);

                for (auto& file2: _files) {
                    if (file2.second.hash == hash) {
                        renamed_files.insert({hash, new_file});
                    }
                }

                _files.insert({shared_file_path, new_file});
            }
            else if (!file.is_blocked && !hash.empty() && file.hash != hash) {
                requests.add(Request(shared_file_path, local_file_path, full_file_path));
                file.is_blocked = true;
                // todo: save temp file only after unblocking -> file.save(local_file_path); https://github.com/DangeL187/SyncWithMe/issues/16
                file.hash = hash;
            }
            files_amount++;
        }
        removeOrRename(files_amount, shared_folder, renamed_files, requests);
    }
}

void FileUpdater::processResponses(Queue<Response>& responses) {
    while (!responses.isEmpty()) {
        Response response = responses.get();

        std::filesystem::path file_path(response.file);
        std::string folder = _shared_folders[file_path.string().substr(0, file_path.string().find('/'))];

        if (folder.empty()) continue;

        File& file = _files[file_path.string()];

        if (!file.isValid()) {
            file = File(folder + "/" + file_path.string().substr(file_path.string().find('/')+1, file_path.string().size()));
            _files.insert({file_path.string(), file});
        }

        file.is_blocked = true;
        file.create();
        file.change(response.changes);
        file.hash = FileHasher::hash(file_path.wstring());
        file.is_blocked = false;
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

                    local_file_path.erase(0, shared_folder.second.size()+1);
                    shared_file_path = shared_folder.first + "/" + local_file_path;
                    local_file_path = "../TEMP/" + shared_file_path;

                    auto renamed_file = renamed_files.find(file.second.hash);
                    if (renamed_file != renamed_files.end()) {
                        std::string renamed_file_path = renamed_file->second.name;
                        std::replace(renamed_file_path.begin(), renamed_file_path.end(), '\\', '/');

                        std::string local_renamed_file_path = renamed_file_path;
                        std::string shared_renamed_file_path;
                        local_renamed_file_path.erase(0, shared_folder.second.size()+1);
                        shared_renamed_file_path = shared_folder.first + "/" + local_renamed_file_path;
                        local_renamed_file_path = "../TEMP/" + shared_renamed_file_path;

                        std::filesystem::rename(local_file_path, local_renamed_file_path);
                        requests.add(Request(shared_file_path, shared_renamed_file_path));
                    } else {
                        std::filesystem::remove(local_file_path);
                        requests.add(Request(shared_file_path, true));
                    }

                    _files.erase(file.first);
                    files_amount--;
                }
            } catch (std::exception& e) {}
            if (files_amount == _files.size()) break;
        }
    }
}
