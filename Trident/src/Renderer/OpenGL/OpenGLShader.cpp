#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cassert>

#include "Utilities/FileUtils.h" // Include this to read files

namespace Engine
{
	static GLuint CompileShader(GLenum type, const std::string& source)
	{
		GLuint shader = glCreateShader(type);
		const char* src = source.c_str();

		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);

			std::cerr << "Shader compilation error:\n" << infoLog << std::endl;
			assert(false);
		}

		return shader;
	}

	OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexSrc = FileUtils::ReadFile(vertexPath);
		std::string fragmentSrc = FileUtils::ReadFile(fragmentPath);

		GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
		GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		glLinkProgram(m_RendererID);

		GLint isLinked;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);

		if (!isLinked)
		{
			char infoLog[512];
			glGetProgramInfoLog(m_RendererID, 512, nullptr, infoLog);
			std::cerr << "Shader link error:\n" << infoLog << std::endl;
			assert(false);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	int OpenGLShader::GetUniformLocation(const std::string& name) const
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
		{
			std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
		}

		return location;
	}
}