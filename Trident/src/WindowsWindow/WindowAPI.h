#pragma once

#include "Events/Event.h"

#include <functional>
#include <memory>

namespace Engine
{
    enum class WindowAPIType
    {
        None = 0,
        OpenGL
    };

    using EventCallbackFn = std::function<void(Event&)>;

    class WindowAPI
    {
    public:
        virtual ~WindowAPI() = default;

        virtual void Init() = 0;
        virtual void* GetNativeWindow() const = 0; // Native pointer to window (GLFWwindow* for OpenGL)
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;

        virtual void CloseWindow() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        static WindowAPIType GetAPI();
        static std::unique_ptr<WindowAPI> Create();
    };
}