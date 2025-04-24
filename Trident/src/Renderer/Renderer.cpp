#include "Renderer.h"

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

	void Renderer::DrawIndexed(unsigned int count)
	{
		m_RendererAPI->DrawIndexed(count);
	}
}