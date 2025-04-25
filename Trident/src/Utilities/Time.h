#pragma once

namespace Engine
{
    class Time
    {
    public:
        static void Init();
        static void Update();

        static float GetTime();          // Total time since start
        static float GetDeltaTime();     // Time between last frame
        static float GetFPS();           // Frames per second

    private:
        static float s_Time;
        static float s_DeltaTime;
        static float s_LastFrame;
        static float s_FPS;
    };

}