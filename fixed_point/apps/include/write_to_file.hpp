#pragma once

#include <sstream>
#include <fstream>
#include <string>

inline bool writeToFile(const std::string &filePath, const std::stringstream &content) {
    std::ofstream file;
    file.open(filePath, std::ios::out);
    if (file.is_open()) {
        file << content.rdbuf();
        file.close();
        return true;
    }
    return false;
}
