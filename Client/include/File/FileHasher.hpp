#ifndef CODEWITHME_FILEHASHER_HPP
#define CODEWITHME_FILEHASHER_HPP

#include <fstream>
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>

/*! @struct FileHasher
    @brief Structure for hashing files
    @det Hashing is generally used to compare file contents
*/
/*! @fn std::string FileHasher::hash(const std::wstring& file_path)
    @brief Get the hashed contents of the file
    @det Uses SHA256 algorithm from OpenSSL
    @param file_path full path to the file to hash
    @return std::string containing the hashed contents of the file
*/

struct FileHasher {
    static std::string hash(const std::wstring& file_path);
};

#endif //CODEWITHME_FILEHASHER_HPP
