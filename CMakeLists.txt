### Workspace ###

cmake_minimum_required(VERSION 3.20)
project(Trident)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Determine configuration name (Debug/Release) for multi-config generators like Visual Studio
get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(IS_MULTI_CONFIG)
  set(OUTPUT_CONFIG "$<CONFIG>")
else()
  set(OUTPUT_CONFIG "${CMAKE_BUILD_TYPE}")
endif()

if (MSVC)
    add_compile_options(/MP)
endif()

# Determine OS and architecture for naming output directories
set(OS_NAME ${CMAKE_SYSTEM_NAME})
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH "x64")
else()
    set(ARCH "x86")
endif()

# Define output directory format: OS-Config-Arch
set(OUTPUT_DIR "${OS_NAME}-${OUTPUT_CONFIG}-${ARCH}/${PROJECT_NAME}")

# Set binary output directories for executables, libraries, and archives
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}")

# Disable GLFW optional components (not needed)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add Trident core engine and Forge application subdirectories
add_subdirectory(Trident)
add_subdirectory(Trident-Forge)

# Add dependency
add_subdirectory(${CMAKE_SOURCE_DIR}/Trident/vendor/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/Trident/vendor/stb)