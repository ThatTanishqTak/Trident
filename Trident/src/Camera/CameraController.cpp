#include "CameraController.h"

#include <GLFW/glfw3.h>

namespace Engine
{
    CameraController::CameraController(float aspectRatio, bool rotation) : m_Camera(45.0f, aspectRatio, 0.01f, 1000.0f), m_AspectRatio(aspectRatio), m_Rotation(rotation)
    {

    }

    void CameraController::OnUpdate(float deltaTime)
    {
        GLFWwindow* window = glfwGetCurrentContext();

        glm::vec3 pos = m_Camera.GetPosition();
        float pitch = m_Camera.GetPitch();
        float yaw = m_Camera.GetYaw();

        glm::vec3 front = glm::normalize(
            glm::vec3
            { 
                cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                sin(glm::radians(pitch)),
                sin(glm::radians(yaw)) * cos(glm::radians(pitch)) 
            });

        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

        // Will use my custom key bindings
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { pos += front * deltaTime * m_MoveSpeed; }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { pos -= front * deltaTime * m_MoveSpeed; }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { pos -= right * deltaTime * m_MoveSpeed; }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { pos += right * deltaTime * m_MoveSpeed; }

        m_Camera.SetPosition(pos);
    }

    void CameraController::OnMouseMove(double xpos, double ypos)
    {
        if (m_FirstMouse)
        {
            m_LastX = xpos;
            m_LastY = ypos;
            m_FirstMouse = false;
        }

        float xOffset = xpos - m_LastX;
        float yOffset = m_LastY - ypos;

        m_LastX = xpos;
        m_LastY = ypos;

        xOffset *= m_MouseSensitivity;
        yOffset *= m_MouseSensitivity;

        float pitch = m_Camera.GetPitch() + yOffset;
        float yaw = m_Camera.GetYaw() + xOffset;

        if (m_Rotation)
        {
            m_Camera.SetRotation(pitch, yaw);
        }
    }

    void CameraController::OnScroll(float yOffset)
    {
        // Optional: zoom functionality
    }

    void CameraController::OnResize(float width, float height)
    {
        m_AspectRatio = width / height;
        m_Camera = PerspectiveCamera(45.0f, m_AspectRatio, 0.1f, 100.0f);
    }

    void CameraController::SetCameraPosition(const glm::vec3& position)
    {
        m_Camera.SetPosition(position);
    }
}