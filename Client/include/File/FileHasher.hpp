#ifndef CODEWITHME_FILEHASHER_HPP
#define CODEWITHME_FILEHASHER_HPP

#include <fstream>
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>

struct FileHasher {
    static std::string calculateHash(const std::string& file_path);
};

#endif //CODEWITHME_FILEHASHER_HPP
