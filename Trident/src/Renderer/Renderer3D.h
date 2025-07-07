#pragma once

#include "Renderer/RenderCommand.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Engine
{
    class Renderer3D
    {
    public:
        static void Init();
        static void Shutdown();
        static void DrawCube(const glm::mat4& model, const glm::mat4& viewProj,
            const glm::vec3& lightPos = glm::vec3{ 2.0f, 4.0f, 2.0f },
            const glm::vec3& lightColor = glm::vec3{ 1.0f },
            float lightIntensity = 1.0f,
            const glm::vec3& viewPos = glm::vec3{ 0.0f });

        static void DrawSphere(const glm::mat4& model, const glm::mat4& viewProj,
            const glm::vec3& lightPos = glm::vec3{ 2.0f, 4.0f, 2.0f },
            const glm::vec3& lightColor = glm::vec3{ 1.0f },
            float lightIntensity = 1.0f,
            const glm::vec3& viewPos = glm::vec3{ 0.0f });

        static void DrawQuad(const glm::mat4& model, const glm::mat4& viewProj,
            const glm::vec3& lightPos = glm::vec3{ 2.0f, 4.0f, 2.0f },
            const glm::vec3& lightColor = glm::vec3{ 1.0f },
            float lightIntensity = 1.0f,
            const glm::vec3& viewPos = glm::vec3{ 0.0f });

        static void DrawPlane(const glm::mat4& model, const glm::mat4& viewProj,
            const glm::vec3& lightPos = glm::vec3{ 2.0f, 4.0f, 2.0f },
            const glm::vec3& lightColor = glm::vec3{ 1.0f },
            float lightIntensity = 1.0f,
            const glm::vec3& viewPos = glm::vec3{ 0.0f });

    private:
        static void DrawGeometry(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Shader>& shader,
            const glm::mat4& model, const glm::mat4& viewProj,
            const glm::vec3& lightPos, const glm::vec3& lightColor,
            float lightIntensity, const glm::vec3& viewPos);
    };
}