#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"

namespace Engine
{
	class Renderer
	{
	public:
		void Init();
		void SetClearColor(float r, float g, float b, float a);
		void Clear();
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

	private:
		std::unique_ptr<RendererAPI> m_RendererAPI;
	};
}