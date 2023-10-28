//
// Created by VrikkaDev on 24/10/2023.
//

#ifndef DUCKENGINE_FILEUTILS_H
#define DUCKENGINE_FILEUTILS_H

namespace DuckEngine {

    class FileUtils {
    public:
        /**
         * Read the contents of a file at a given file path and return it as a string.
         * Returns empty if file not found
         */
        static std::string ReadFileString(const char* filePath);

        /**
         * Read the contents of a file at a given relative file path and return it as a string.
         * The file path is relative to the parent directory of the current working directory.
         * Returns empty if file not found
         **/
        static std::string ReadRelativeFileString(const char* filePath);
    };

} // DuckEngine
#endif //DUCKENGINE_FILEUTILS_H
