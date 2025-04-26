#include "Renderer.h"
#include "Renderer/RenderCommand.h"

namespace Engine {

	static std::shared_ptr<RenderPass> s_ActiveRenderPass;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(const std::shared_ptr<RenderPass>& renderPass)
	{
		s_ActiveRenderPass = renderPass;
		s_ActiveRenderPass->Begin();
	}

	void Renderer::EndScene()
	{
		s_ActiveRenderPass->End();
	}

	void Renderer::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		RenderCommand::DrawIndexed(vertexArray);
	}
}