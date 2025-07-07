#pragma once

#include <filesystem>
#include <string>

class ContentBrowserPanel
{
public:
    ContentBrowserPanel(const std::string& assetsDirectory = "Assets");

    void OnImGuiRender();

private:
    std::filesystem::path m_AssetsDirectory;
    std::filesystem::path m_CurrentDirectory;
};