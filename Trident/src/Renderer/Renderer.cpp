#include "Renderer.h"
#include "VertexArray.h"

namespace Engine
{
	void Renderer::Init()
	{
		m_RendererAPI = RendererAPI::Create();
		m_RendererAPI->Init();
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		m_RendererAPI->SetClearColor(r, g, b, a);
	}

	void Renderer::Clear()
	{
		m_RendererAPI->Clear();
	}

	void Renderer::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		m_RendererAPI->DrawIndexed(vertexArray->GetIndexBuffer()->GetCount());
	}
}