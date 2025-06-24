#include "FileUtils.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Engine
{
    std::string FileUtils::ReadFile(const std::string& filepath)
    {
        std::ifstream fileStream(filepath, std::ios::in);

        if (!fileStream.is_open())
        {
            std::cerr << "Failed to open file: " << filepath << std::endl;

            return "";
        }

        std::stringstream buffer;
        buffer << fileStream.rdbuf();

        fileStream.close();

        return buffer.str();
    }
}