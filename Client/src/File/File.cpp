#include "File/File.hpp"

File::File() = default;

File::File(const std::string& name) {
    this->name = name;
}

File::File(const std::string& name, const std::string& hash) {
    this->name = name;
    this->hash = hash;
}

#include <iostream> // todo: delete

void File::change(const std::unordered_map<std::string, std::string>& changes) const {
    bool        is_added;
    bool        is_deleted;
    bool        is_last = false;
    long long   old_lines = 1;
    long long   new_lines = 1;

    std::ifstream file(std::filesystem::path(name).c_str());

    if (!file.is_open()) return;

    std::string line;
    while (true) {
        if (is_last) break;
        if (!file.good()) is_last = true;
        std::getline(file, line);

        while (true) {
            auto added_line = changes.find(std::to_string(new_lines));

            is_added = added_line != changes.end();
            is_deleted = changes.find("-" + std::to_string(old_lines)) != changes.end();

            if ((!is_deleted || is_added)) {
                if (is_added) std::cout << added_line->second << "\n";
                else if (!is_last) std::cout << line << "\n";
                new_lines++;
            }

            if (is_deleted == is_added) {
                old_lines++;
                break;
            }
        }
    }
    file.close();
}

void File::create() const {
    std::filesystem::path file_path(name);
    if (!std::filesystem::exists(file_path)) {
        std::filesystem::create_directory(file_path.parent_path());
        std::ofstream(file_path.c_str()).close();
    }
}

bool File::isValid() const {
    return !name.empty();
}

void File::save(const std::string& local_file_path) const {
    try {
        if (std::filesystem::exists(local_file_path)) {
            std::filesystem::remove(local_file_path);
            std::filesystem::copy(name, local_file_path);
        } else {
            std::filesystem::create_directory(std::filesystem::path(local_file_path).parent_path());
            std::filesystem::copy(name, local_file_path);
        }
    } catch (std::exception& e) {}
}
