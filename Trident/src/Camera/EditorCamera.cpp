#include "EditorCamera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Engine
{
    EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip) : m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
    {
        UpdateProjection();
        UpdateView();
    }

    void EditorCamera::SetViewportSize(float width, float height)
    {
        m_AspectRatio = width / height;
    
        UpdateProjection();
    }

    void EditorCamera::UpdateProjection()
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void EditorCamera::UpdateView()
    {
        glm::vec3 front{};
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Direction = glm::normalize(front);

        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void EditorCamera::OnUpdate(float deltaTime)
    {
        GLFWwindow* window = glfwGetCurrentContext();
        if (!window || !m_RightMousePressed)
        {
            return;
        }

        float speed = m_Speed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            speed *= 2.5f;
        }

        glm::vec3 right = glm::normalize(glm::cross(m_Direction, m_Up));
        glm::vec3 up = glm::normalize(glm::cross(right, m_Direction));

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            m_Position += m_Direction * speed;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            m_Position -= m_Direction * speed;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            m_Position -= right * speed;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            m_Position += right * speed;
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            m_Position -= up * speed;
        }

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            m_Position += up * speed;
        }

        UpdateView();

        std::cout << "Camera Position: " << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << std::endl;
    }

    void EditorCamera::OnMouseScroll(float delta)
    {
        m_Position += m_Direction * delta * 0.5f;
    
        UpdateView();
    }

    void EditorCamera::OnMouseMove(float xpos, float ypos)
    {
        if (!m_RightMousePressed)
        {
            return;
        }

        if (m_FirstMouse)
        {
            m_LastX = xpos;
            m_LastY = ypos;
            m_FirstMouse = false;
        }

        float xOffset = xpos - m_LastX;
        float yOffset = m_LastY - ypos; // reversed since y-coordinates go from bottom to top

        m_LastX = xpos;
        m_LastY = ypos;

        xOffset *= m_MouseSensitivity;
        yOffset *= m_MouseSensitivity;

        m_Yaw += xOffset;
        m_Pitch += yOffset;

        // Constrain pitch
        if (m_Pitch > 89.0f) m_Pitch = 89.0f;
        if (m_Pitch < -89.0f) m_Pitch = -89.0f;

        UpdateView();
    }

    void EditorCamera::OnMouseButton(int button, int action)
    {
        if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            if (action == GLFW_PRESS)
            {
                m_RightMousePressed = true;
                m_FirstMouse = true;
            
                glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }

            else if (action == GLFW_RELEASE)
            {
                m_RightMousePressed = false;
                
                glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
    }

    void EditorCamera::OnKeyInput(int key, int action)
    {
        // Not needed unless you're implementing per-key logic outside Update()
    }
}