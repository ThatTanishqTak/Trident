#pragma once

// Platform detection
#ifdef _WIN32
	#define TRIDENT_PLATFORM_WINDOWS
#else
	#error Trident only supports Windows at the moment!
#endif

// DLL export/import
#ifdef TRIDENT_PLATFORM_WINDOWS
#ifdef TRIDENT_BUILD_DLL
	#define TRIDENT_API __declspec(dllexport)
#else
	#define TRIDENT_API __declspec(dllimport)
#endif
#else
	#define TRIDENT_API
#endif

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
#include <GLFW/glfw3.h>

// Engine Core Headers
