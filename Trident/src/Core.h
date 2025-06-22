#pragma once

// Standard Library Headers
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <utility>
#include <functional>

// GLAD / OpenGL / GLFW
#include <glad/glad.h>

// Engine Core Headers
#include "WindowsWindow/WindowsWindow.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer3D.h"
#include "Renderer/RenderPass.h"
#include "Renderer/OpenGL/OpenGLRenderPass.h"

#include "Camera/CameraController.h"
#include "Camera/PerspectiveCamera.h"
#include "Camera/EditorCamera.h"

#include "ImGui/ImGuiLayer.h"

#include "Utilities/Time.h"

#include "ECS/Entity.h"
#include "ECS/Registry.h"