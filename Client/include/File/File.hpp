#ifndef CODEWITHME_FILE_HPP
#define CODEWITHME_FILE_HPP

#include <string>
#include <filesystem>

struct File {
    std::string name;
    std::string hash;
    bool        is_blocked = false;

    explicit File(const std::string& name);
    File(const std::string& name, const std::string& hash);

    void save(const std::string& local_file_path) const;
};

#endif //CODEWITHME_FILE_HPP
