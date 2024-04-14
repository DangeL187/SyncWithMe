#include "File/File.hpp"

File::File(const std::string& name) {
    this->name = name;
}

File::File(const std::string& name, const std::string& hash) {
    this->name = name;
    this->hash = hash;
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
