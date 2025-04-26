#include "RenderCommand.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace Engine
{
	void RendererCommand::Init()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void RendererCommand::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RendererCommand::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RendererCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}