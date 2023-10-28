//
// Created by VrikkaDev on 24/10/2023.
//

#include "FileUtils.h"

namespace DuckEngine {
    std::string FileUtils::ReadFileString(const char* filePath) {
        std::string content = std::string();

        // Try to open the file at the given file path.
        std::ifstream file_stream(filePath, std::ios::in);

        // If the file could not be opened, try to read it from the parent
        // directory of the current working directory.
        if(!file_stream.is_open()){
            return ReadRelativeFileString(filePath);
        }

        // Read the file line by line and append each line to the content string.
        std::string line = "";
        while(!file_stream.eof()){
            std::getline(file_stream, line);
            content.append(line + "\n");
        }

        // Close the file stream and return the content string.
        file_stream.close();
        return content;
    }

    std::string FileUtils::ReadRelativeFileString(const char* filePath) {
        std::string content = std::string();

        // Construct the full file path by appending the given file path to
        // the parent directory of the current working directory.
        std::ifstream file_stream((std::filesystem::current_path().parent_path().append(filePath)), std::ios::in);

        // If the file could not be opened, return an error message.
        if(!file_stream.is_open()){
            return "";
        }

        // Read the file line by line and append each line to the content string.
        std::string line = "";
        while(!file_stream.eof()){
            std::getline(file_stream, line);
            content.append(line + "\n");
        }

        // Close the file stream and return the content string.
        file_stream.close();
        return content;
    }
} // DuckEngine