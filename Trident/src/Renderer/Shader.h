#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Engine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// Uniform setting
		virtual void SetUniformInt(const std::string& name, int value) = 0;
		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		static std::shared_ptr<Shader> Create(const std::string& vertexPath, const std::string& fragmentPath);
	};
}