#pragma once

#include "Renderer/RendererAPI.h"

namespace Engine
{
	class OpenGLRenderer : public RendererAPI
	{
	public:
		void Init() override;
		void SetClearColor(float r, float g, float b, float a) override;
		void Clear() override;
		void DrawIndexed(uint32_t count) override;
	};
}