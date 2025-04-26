#pragma once

#include "RenderPass.h"
#include <memory>

namespace Engine
{
	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(const std::shared_ptr<RenderPass>& renderPass);
		static void EndScene();
		static void DrawIndexed(const std::shared_ptr<class VertexArray>& vertexArray);
	};
}