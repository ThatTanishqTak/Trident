#pragma once

#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/RenderCommand.h"

#include <glm/glm.hpp>

namespace Engine
{
    class Renderer3D
    {
    public:
        static void Init();
        static void Shutdown();
        static void DrawCube(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos);
        static void DrawSphere(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos);
        static void DrawQuad(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos);
        static void DrawPlane(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos);

    private:
        static void DrawGeometry(const std::shared_ptr<VertexArray>& vao, const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos);
    };
}