#include "File/FileHasher.hpp"

#include <iostream>

std::string FileHasher::hash(const std::wstring& file_path) {
    std::ifstream f(file_path.c_str(), std::ios::binary);
    if (!f.is_open()) {
        return "";
    }

    std::stringstream ss;
    unsigned char buffer[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    while (!f.eof()) {
        f.read(reinterpret_cast<char*>(buffer), sizeof(buffer));
        SHA256_Update(&sha256, buffer, f.gcount());
    }

    SHA256_Final(buffer, &sha256);
    for (unsigned char i: buffer) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)i;
    }

    f.close();
    return ss.str();
}