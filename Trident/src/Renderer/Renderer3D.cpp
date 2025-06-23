#include "Renderer3D.h"

#include "Renderer/BufferLayout.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

#include "Geometry/Geometry.h"

namespace Engine
{
    namespace
    {
        struct Resources
        {
            std::shared_ptr<VertexArray> VertexArray;
            std::shared_ptr<Shader> Shader;
        } s_Resources;
    }

    void Renderer3D::Init()
    {
        if (s_Resources.Shader)
        {
            return;
        }

        s_Resources.Shader = Shader::Create("Assets/Shaders/Basic.vert", "Assets/Shaders/Basic.frag");
    }

    void Renderer3D::Shutdown()
    {
        s_Resources.Shader.reset();
    }

    void Renderer3D::DrawGeometry(const std::shared_ptr<VertexArray>& vao, const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos)
    {
        if (!s_Resources.Shader)
        {
            Init();
        }

        s_Resources.Shader->Bind();
        s_Resources.Shader->SetUniformMat4("u_Model", model);
        s_Resources.Shader->SetUniformMat4("u_ViewProjection", viewProj);
        s_Resources.Shader->SetUniformFloat3("u_LightPos", lightPos);
        s_Resources.Shader->SetUniformFloat3("u_LightColor", lightColor);
        s_Resources.Shader->SetUniformFloat("u_LightIntensity", lightIntensity);
        s_Resources.Shader->SetUniformFloat3("u_ViewPos", viewPos);

        RenderCommand::DrawIndexed(vao);
    }

    void Renderer3D::DrawCube(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos)
    {
        DrawGeometry(Geometry::GetCube(), model, viewProj, lightPos, lightColor, lightIntensity, viewPos);
    }

    void Renderer3D::DrawSphere(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos)
    {
        DrawGeometry(Geometry::GetSphere(), model, viewProj, lightPos, lightColor, lightIntensity, viewPos);
    }

    void Renderer3D::DrawQuad(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos)
    {
        DrawGeometry(Geometry::GetQuad(), model, viewProj, lightPos, lightColor, lightIntensity, viewPos);
    }

    void Renderer3D::DrawPlane(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos)
    {
        DrawGeometry(Geometry::GetPlane(), model, viewProj, lightPos, lightColor, lightIntensity, viewPos);
    }
}