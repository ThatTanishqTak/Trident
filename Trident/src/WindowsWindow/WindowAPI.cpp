#include "WindowAPI.h"
#include "OpenGL/OpenGLWindow.h"

namespace Engine
{
	static WindowAPIType s_API = WindowAPIType::OpenGL;

	WindowAPIType WindowAPI::GetAPI()
	{
		return s_API;
	}

	std::unique_ptr<WindowAPI> WindowAPI::Create()
	{
		switch (s_API)
		{
			case WindowAPIType::OpenGL:
			{
				return std::make_unique<OpenGLWindow>();
			}

			case WindowAPIType::None:
			default:
			{
				return nullptr;
			}
		}
	}
}