#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	class Camera
	{
	public:
		virtual ~Camera() = default;

		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual glm::mat4 GetViewProjectionMatrix() const = 0;
	};
}