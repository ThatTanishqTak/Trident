#pragma once

// Standard Library Headers
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// GLAD / OpenGL / GLFW
#include <glad/glad.h>

// Engine Core Headers
#include "WindowsWindow/WindowsWindow.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Geometry/Geometry.h"

#include "Renderer/Framebuffer.h"
#include "Renderer/OpenGL/OpenGLRenderPass.h"
#include "Renderer/RenderPass.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer3D.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

#include "Camera/CameraController.h"
#include "Camera/EditorCamera.h"
#include "Camera/PerspectiveCamera.h"

#include "ImGui/ImGuiLayer.h"

#include "Utilities/Time.h"

#include "ECS/Entity.h"
#include "ECS/Registry.h"