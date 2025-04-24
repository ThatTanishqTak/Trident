#pragma once

#include <string>

namespace Engine
{
    // Utility class for file I/O operations.
    class FileUtils
    {
    public:
        // Reads the entire contents of a text file and returns it as a string.
        static std::string ReadFile(const std::string& filepath);
    };
}