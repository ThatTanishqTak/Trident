#pragma once

#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include <glm/glm.hpp>
#include <array>
#include <memory>

namespace Engine
{
    class Skybox
    {
    public:
        static void Init(const std::array<std::string, 6>& faces);
        static void Shutdown();
        static void Draw(const glm::mat4& view, const glm::mat4& projection);

    private:
        static std::shared_ptr<Shader> s_Shader;
        static std::shared_ptr<VertexArray> s_VAO;
        static unsigned int s_TextureID;
    };
}