#pragma once

#include "Shader.h"

namespace Engine
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        void Init();
        void Render();
        void Shutdown();

    private:
        GLuint m_VAO;
        GLuint m_VBO;

        class Shader* m_Shader;
    };
}