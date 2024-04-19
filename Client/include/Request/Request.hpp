#ifndef CODEWITHME_REQUEST_HPP
#define CODEWITHME_REQUEST_HPP

#include <fstream>
#include <string>

#include "dtl.hpp"
#include "json.hpp"

/*! @class Request
    @brief Class that describes specific request that can be sent to show file changes
*/
/*! @fn Request::Request()
    @brief Create invalid request
*/
/*! @fn Request::Request(const std::string& shared_file_path, const std::string& old_file_path, const std::string& new_file_path)
    @brief Create request that describes how the file was changed
    @param shared_file_path File path but related to the <b> shared </b> folder
    @param old_file_path ?
    @param new_file_path ?
*/
/*! @var Request::_data
    @brief Contains information about file's recent changes
    @det Uses data type from dtl.hpp
*/
/*! @var Request::_file_path
    @brief Contains shared file path 
*/
/*! @var Request::_is_deleted
    @brief Was file deleted or not 
*/
/*! @var Request::_is_valid
    @brief Is request valid. It is invalid only when creating Request like this - Request() 
*/
/*! @var Request::_new_file_name
    @brief File's new name after renaming
*/

class Request {
public:
    Request();
    Request(const std::string& shared_file_path, const std::string& old_file_path, const std::string& new_file_path);
    Request(const std::string& shared_file_path, const std::string& new_file_name);
    Request(const std::string& shared_file_path, bool is_deleted);

    std::string toJson();

    [[nodiscard]] bool isValid() const;

private:
    dtl::Diff<std::string, std::vector<std::string>>    _data;
    std::string                                         _file_path;
    bool                                                _is_deleted = false;
    bool                                                _is_valid = true;
    std::string                                         _new_file_name;

    void generateData(const std::vector<std::string>& old_contents, const std::vector<std::string>& new_contents);
};

#endif //CODEWITHME_REQUEST_HPP
