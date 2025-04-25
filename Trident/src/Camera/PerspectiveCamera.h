#pragma once

#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	class PerspectiveCamera : public Camera
	{
	public:
        PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip);

        void SetPosition(const glm::vec3& position);
        void SetRotation(float pitch, float yaw);

        const glm::vec3& GetPosition() const { return m_Position; }
        float GetPitch() const { return m_Pitch; }
        float GetYaw() const { return m_Yaw; }

        void RecalculateView();

        virtual const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
        virtual const glm::mat4& GetViewMatrix() const override { return m_ViewMatrix; }
        virtual glm::mat4 GetViewProjectionMatrix() const override;

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::vec3 m_Position = { 0.0f, 0.0f, 3.0f };

        float m_Pitch = 0.0f;
        float m_Yaw = -90.0f;

        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
	};
}