#ifndef CODEWITHME_FILE_HPP
#define CODEWITHME_FILE_HPP

#include <string>
#include <filesystem>
#include <fstream>
#include <unordered_map>

/*! @struct File
    @brief Structure describing default file's properties
*/
/*! @var File::name
    @brief File's full path
*/
/*! @var File::hash
    @brief Represents file's hashed content that is used to compare files
*/
/*! @var File::is_blocked
    @brief A flag indicating whether interaction with this file is allowed or not
*/
/*! @fn File::File()
    @brief Create an invalid File object
    @det Used to represent a File that was not found
*/
/*! @fn File::File(const std::string& name)
    @brief Create a File object with specified name
    @param name File's full path
*/
/*! @fn File::File(const std::string& name, const std::string& hash)
    @brief Create a File object with specified name and hash value
    @param name File's full path
    @param hash File's hash value
*/
/*! @fn void File::change(const std::unordered_map<std::string, std::string>& changes)
    @brief Changes the contents of a file according to "changes" parameter
    @det todo: add more info
    @param changes Unordered map containing changes
*/
/*! @fn void File::create()
    @brief Creates a file using "name" field as a path
    @det If file already exists - does nothing
*/
/*! @fn bool File::isValid()
    @brief Check whether File object is valid or not
    @det Invalid means that the "name" field is empty
    @return true if File is valid, false if not
*/
/*! @fn void File::save(const std::string& local_file_path)
    @brief Save a temp copy of the file in local_file_path
    @det Saves a temp file at local_file_path that is a copy of this File
    @det The temp file is used as reference to track updates
    @det 1. If temp file exists - removes old file and saves a copy in it
    @det    It requires deletion and further copying due to a bug related to std::filesystem
    @det 2. If temp file does not exist - creates a directory and saves a copy in it
*/

struct File {
    std::string name;
    std::string hash;
    bool        is_blocked = false;

    File();
    explicit File(const std::string& name);
    File(const std::string& name, const std::string& hash);

    void change(const std::unordered_map<std::string, std::string>& changes) const;
    void create() const;
    [[nodiscard]] bool isValid() const;
    void save(const std::string& local_file_path) const;
};

#endif //CODEWITHME_FILE_HPP
