#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace Engine
{
    class ImGuiLayer
    {
    public:
        void Init(GLFWwindow* window);
        void Begin();
        void End();
        void Shutdown();
    };
}