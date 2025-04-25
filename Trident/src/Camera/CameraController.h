#pragma once

#include "PerspectiveCamera.h"

namespace Engine
{
    class CameraController
    {
    public:
        CameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(float deltaTime);
        void OnMouseMove(double xpos, double ypos);
        void OnScroll(float yOffset);
        void OnResize(float width, float height);

        const PerspectiveCamera& GetCamera() const { return m_Camera; }

    private:
        PerspectiveCamera m_Camera;
        float m_AspectRatio;

        bool m_FirstMouse = true;
        float m_LastX = 0.0f, m_LastY = 0.0f;
        float m_MouseSensitivity = 0.1f;
        float m_MoveSpeed = 5.0f;

        bool m_Rotation;
    };
}