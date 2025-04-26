#pragma once

#include "Renderer/Framebuffer.h"

#include <glm/glm.hpp>
#include <memory>

namespace Engine
{
	struct RenderPassSpecification
	{
		glm::vec4 ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };
		std::shared_ptr<Framebuffer> TargetFramebuffer = nullptr;
	};

	class RenderPass
	{
	public:
		virtual ~RenderPass() = default;

		virtual void Begin() = 0;
		virtual void End() = 0;

		const RenderPassSpecification& GetSpecification() const { return m_Specification; }

	protected:
		RenderPassSpecification m_Specification;
	};
}