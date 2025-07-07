#include "Skybox.h"
#include "Geometry/Geometry.h"
#include <string>
#include <glad/glad.h>
#include "Renderer/RenderCommand.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Engine
{
    std::shared_ptr<Shader> Skybox::s_Shader;
    std::shared_ptr<VertexArray> Skybox::s_VAO;
    unsigned int Skybox::s_TextureID = 0;

    static unsigned int LoadCubemap(const std::array<std::string, 6>& faces)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        stbi_set_flip_vertically_on_load(false);
        for (unsigned int i = 0; i < faces.size(); ++i)
        {
            int width, height, channels;
            unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            else
            {
                stbi_image_free(data);
            }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return textureID;
    }

    void Skybox::Init(const std::array<std::string, 6>& faces)
    {
        if (s_Shader)
        {
            return;
        }

        s_Shader = Shader::Create("Assets/Shaders/Skybox.vert", "Assets/Shaders/Skybox.frag");
        s_VAO = Geometry::GetCube();
        s_TextureID = LoadCubemap(faces);
    }

    void Skybox::Shutdown()
    {
        s_Shader.reset();
        s_VAO.reset();
        if (s_TextureID)
        {
            glDeleteTextures(1, &s_TextureID);
            s_TextureID = 0;
        }
    }

    void Skybox::Draw(const glm::mat4& view, const glm::mat4& projection)
    {
        if (!s_Shader)
        {
            return;
        }

        glDepthFunc(GL_LEQUAL);
        s_Shader->Bind();
        glm::mat4 vp = projection * glm::mat4(glm::mat3(view));
        s_Shader->SetUniformMat4("u_ViewProjection", vp);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, s_TextureID);
        s_Shader->SetUniformInt("u_Skybox", 0);
        RenderCommand::DrawIndexed(s_VAO);
        glDepthFunc(GL_LESS);
    }
}