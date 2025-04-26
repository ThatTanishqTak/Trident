#pragma once

#include "Renderer/RenderPass.h"

namespace Engine
{
	class OpenGLRenderPass : public RenderPass
	{
	public:
		OpenGLRenderPass(const RenderPassSpecification& spec);

		virtual void Begin() override;
		virtual void End() override;
	};
}