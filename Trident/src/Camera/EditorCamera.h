#pragma once

#include "Camera/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    class EditorCamera : public Camera
    {
    public:
        EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

        void SetPosition(const glm::vec3& position)
        {
            m_Position = position;
            UpdateView();
        }
        const glm::vec3& GetPosition() const { return m_Position; }

        void OnUpdate(float deltaTime);
        void OnMouseScroll(float delta);
        void OnMouseMove(float xOffset, float yOffset);
        void OnKeyInput(int key, int action);
        void OnMouseButton(int button, int action);
        void SetViewportSize(float width, float height);

        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
        glm::mat4 GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }
        const glm::mat4& GetViewProjection() const { return m_ViewProjectionMatrix; }

        void UpdateView();
        void UpdateProjection();

    private:
        glm::vec3 m_Position = { 0.0f, 0.0f, 5.0f };
        glm::vec3 m_Direction;
        glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };

        float m_FOV;
        float m_AspectRatio;
        float m_NearClip;
        float m_FarClip;
        float m_Pitch = 0.0f, m_Yaw = -90.0f;
        float m_MouseSensitivity = 0.1f;
        float m_Speed = 5.0f;

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        bool m_FirstMouse = true;
        float m_LastX = 0.0f, m_LastY = 0.0f;

        bool m_RightMousePressed = false;
    };
}