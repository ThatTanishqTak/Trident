#include "ContentBrowserPanel.h"

#include <imgui.h>

ContentBrowserPanel::ContentBrowserPanel(const std::string& assetsDirectory) : m_AssetsDirectory(assetsDirectory), m_CurrentDirectory(m_AssetsDirectory)
{

}

void ContentBrowserPanel::OnImGuiRender()
{
    ImGui::Begin("Content Browser");

    if (m_CurrentDirectory != m_AssetsDirectory)
    {
        if (ImGui::Button("<-"))
        {
            m_CurrentDirectory = m_CurrentDirectory.parent_path();
        }
    }

    for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
    {
        const auto& path = directoryEntry.path();
        auto relativePath = std::filesystem::relative(path, m_AssetsDirectory);
        std::string filenameString = relativePath.filename().string();

        ImGui::Button(filenameString.c_str(), ImVec2(100, 100));

        if (ImGui::BeginDragDropSource())
        {
            const wchar_t* itemPath = path.c_str();
            ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
            ImGui::Text("%s", filenameString.c_str());
            ImGui::EndDragDropSource();
        }

        if (directoryEntry.is_directory() && ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            m_CurrentDirectory /= path.filename();
        }

        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && !directoryEntry.is_directory())
        {
            // File selected - add functionality as needed
        }

        ImGui::NextColumn();
    }

    ImGui::End();
}