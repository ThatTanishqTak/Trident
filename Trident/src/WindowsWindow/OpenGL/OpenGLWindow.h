#pragma once

#include "WindowsWindow/WindowAPI.h"

#include <functional>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine
{
    class OpenGLWindow : public WindowAPI
    {
    public:
        ~OpenGLWindow();

        void Init() override;
        void* GetNativeWindow() const override;
        int GetWidth() const override;
        int GetHeight() const override;

        void CloseWindow() const override;

        void SetEventCallback(const EventCallbackFn& callback) override { m_EventCallback = callback; }

    private:
        GLFWwindow* m_Window = nullptr;
        EventCallbackFn m_EventCallback;

        static void GLFWErrorCallback(int error, const char* description);

        int m_Width = 1920;
        int m_Height = 1080;
    };
}