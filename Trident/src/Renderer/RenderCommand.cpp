#include "RenderCommand.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace Engine
{
    void RenderCommand::Init() { glEnable(GL_DEPTH_TEST); }

    void RenderCommand::SetClearColor(const glm::vec4& color) { glClearColor(color.r, color.g, color.b, color.a); }

    void RenderCommand::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}