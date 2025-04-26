#include "Time.h"

#include <GLFW/glfw3.h>

namespace Engine
{
    float Time::s_Time = 0.0f;
    float Time::s_DeltaTime = 0.0f;
    float Time::s_LastFrame = 0.0f;
    float Time::s_FPS = 0.0f;

    void Time::Init()
    {
        s_Time = static_cast<float>(glfwGetTime());
        s_LastFrame = s_Time;
    }

    void Time::Update()
    {
        s_Time = static_cast<float>(glfwGetTime());
        s_DeltaTime = s_Time - s_LastFrame;
        s_LastFrame = s_Time;

        if (s_DeltaTime > 0.0f)
        {
            s_FPS = 1.0f / s_DeltaTime;
        }
    }

    float Time::GetTime()
    {
        return s_Time;
    }

    float Time::GetDeltaTime()
    {
        return s_DeltaTime;
    }

    float Time::GetFPS()
    {
        return s_FPS;
    }
}