#include "Renderer3D.h"
#include "Renderer/BufferLayout.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

namespace Engine
{
    namespace
    {
        struct CubeResources
        {
            std::shared_ptr<VertexArray> VertexArray;
            std::shared_ptr<Shader> Shader;
        } s_Cube;
    }

    void Renderer3D::Init()
    {
        if (s_Cube.VertexArray)
        {
            return;
        }

        float vertices[] =
        {
            // Back face (-Z)
           -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
           -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
           // Front face (+Z)
          -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
           0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
          -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 1.0f,   0.0f,  0.0f,  1.0f,
          // Left face (-X)
         -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
         -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
         -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 1.0f,  -1.0f,  0.0f,  0.0f,
         // Right face (+X)
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         // Bottom face (-Y)
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
        // Top face (+Y)
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 1.0f,   0.0f,  1.0f,  0.0f
        };

        uint32_t indices[] =
        {
             0,  1,  2,  2,  3,  0,
             4,  5,  6,  6,  7,  4,
             8,  9, 10, 10, 11,  8,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 23, 20
        };

        auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color"    },
            { ShaderDataType::Float3, "a_Normal"   }
        };
        vertexBuffer->SetLayout(layout);

        auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        s_Cube.VertexArray = VertexArray::Create();
        s_Cube.VertexArray->AddVertexBuffer(vertexBuffer);
        s_Cube.VertexArray->SetIndexBuffer(indexBuffer);

        s_Cube.Shader = Shader::Create("Assets/Shaders/Basic.vert", "Assets/Shaders/Basic.frag");
    }

    void Renderer3D::Shutdown()
    {
        s_Cube.VertexArray.reset();
        s_Cube.Shader.reset();
    }

    void Renderer3D::DrawCube(const glm::mat4& model, const glm::mat4& viewProj, const glm::vec3& lightPos, const glm::vec3& lightColor, float lightIntensity, const glm::vec3& viewPos)
    {
        if (!s_Cube.VertexArray)
        {
            Init();
        }

        s_Cube.Shader->Bind();
        s_Cube.Shader->SetUniformMat4("u_Model", model);
        s_Cube.Shader->SetUniformMat4("u_ViewProjection", viewProj);
        s_Cube.Shader->SetUniformFloat3("u_LightPos", lightPos);
        s_Cube.Shader->SetUniformFloat3("u_LightColor", lightColor);
        s_Cube.Shader->SetUniformFloat("u_LightIntensity", lightIntensity);
        s_Cube.Shader->SetUniformFloat3("u_ViewPos", viewPos);

        RenderCommand::DrawIndexed(s_Cube.VertexArray);
    }
}