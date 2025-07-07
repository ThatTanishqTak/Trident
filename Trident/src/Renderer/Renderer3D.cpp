#include "Renderer3D.h"

#include "Renderer/BufferLayout.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"

#include "Geometry/Geometry.h"

namespace Engine
{
    namespace
    {
        struct Resources
        {
            std::shared_ptr<VertexArray> VertexArray;
            std::shared_ptr<Shader> CubeShader;
            std::shared_ptr<Shader> SphereShader;
            std::shared_ptr<Shader> QuadShader;
        } s_Resources;
    }

    void Renderer3D::Init()
    {
        if (s_Resources.CubeShader && s_Resources.SphereShader && s_Resources.QuadShader)
        {
            return;
        }

        s_Resources.CubeShader = Shader::Create("Assets/Shaders/Cube.vert", "Assets/Shaders/Cube.frag");
        s_Resources.SphereShader = Shader::Create("Assets/Shaders/Sphere.vert", "Assets/Shaders/Sphere.frag");
        s_Resources.QuadShader = Shader::Create("Assets/Shaders/Quad.vert", "Assets/Shaders/Quad.frag");
    }

    void Renderer3D::Shutdown()
    {
        s_Resources.CubeShader.reset();
        s_Resources.SphereShader.reset();
        s_Resources.QuadShader.reset();
    }

    void Renderer3D::DrawGeometry(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Shader>& shader,
        const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor,
        float lightIntensity, const glm::vec3& viewPos)
    {
        Init();

        shader->Bind();
        shader->SetUniformMat4("u_Model", model);
        shader->SetUniformMat4("u_ViewProjection", viewProj);
        shader->SetUniformFloat3("u_LightPos", lightPos);
        shader->SetUniformFloat3("u_LightColor", lightColor);
        shader->SetUniformFloat("u_LightIntensity", lightIntensity);
        shader->SetUniformFloat3("u_ViewPos", viewPos);

        RenderCommand::DrawIndexed(vao);
    }

    void Renderer3D::DrawCube(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos)
    {
        DrawGeometry(Geometry::GetCube(), s_Resources.CubeShader, model, viewProj, lightPos, lightColor, lightIntensity, viewPos);
    }

    void Renderer3D::DrawSphere(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos)
    {
        DrawGeometry(Geometry::GetSphere(), s_Resources.SphereShader, model, viewProj, lightPos, lightColor, lightIntensity, viewPos);
    }

    void Renderer3D::DrawQuad(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos)
    {
        DrawGeometry(Geometry::GetQuad(), s_Resources.QuadShader, model, viewProj, lightPos, lightColor, lightIntensity, viewPos);
    }

    void Renderer3D::DrawPlane(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos)
    {
        DrawGeometry(Geometry::GetPlane(), s_Resources.QuadShader, model, viewProj, lightPos, lightColor, lightIntensity, viewPos);
    }
}