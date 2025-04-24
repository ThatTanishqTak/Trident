#pragma once

#include "RendererAPI.h"

namespace Engine
{
	class Renderer
	{
	public:
		void Init();
		void SetClearColor(float r, float g, float b, float a);
		void Clear();
		void DrawIndexed(unsigned int count);

	private:
		std::unique_ptr<RendererAPI> m_RendererAPI;
	};
}