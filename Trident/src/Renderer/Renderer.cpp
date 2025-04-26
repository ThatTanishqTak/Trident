#include "Renderer.h"
#include "VertexArray.h"

namespace Engine
{
	void Renderer::Init()
	{
		RendererCommand::Init();
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		RendererCommand::SetClearColor(glm::vec4(r, g, b, a));
	}

	void Renderer::Clear()
	{
		RendererCommand::Clear();
	}

	void Renderer::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		RendererCommand::DrawIndexed(vertexArray);
	}
}