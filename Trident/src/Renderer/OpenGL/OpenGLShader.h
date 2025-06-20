#pragma once

#include "Renderer/Shader.h"

namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniformInt(const std::string& name, int value) override;
		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetUniformFloat(const std::string& name, float value) override;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) override;

	private:
		uint32_t m_RendererID;

		int GetUniformLocation(const std::string& name) const;
	};
}