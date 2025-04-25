#pragma once

#include <memory>

namespace Engine
{
	enum class RendererAPIType
	{
		None = 0,
		OpenGL
	};

	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(uint32_t count) = 0;

		static RendererAPIType GetAPI();
		static std::unique_ptr<RendererAPI> Create();
	};
}