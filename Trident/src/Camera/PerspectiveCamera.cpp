#include "PerspectiveCamera.h"

namespace Engine
{
    PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);

        RecalculateView();
    }

    void PerspectiveCamera::SetPosition(const glm::vec3& position)
    {
        m_Position = position;

        RecalculateView();
    }

    void PerspectiveCamera::SetRotation(float pitch, float yaw)
    {
        m_Pitch = pitch;
        m_Yaw = yaw;

        RecalculateView();
    }

    void PerspectiveCamera::RecalculateView()
    {
        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        direction.y = sin(glm::radians(m_Pitch));
        direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

        m_Front = glm::normalize(direction);
        m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));

        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    glm::mat4 PerspectiveCamera::GetViewProjectionMatrix() const { return m_ProjectionMatrix * m_ViewMatrix; }
}