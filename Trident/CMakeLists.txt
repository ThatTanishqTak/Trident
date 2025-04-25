project(Trident)

# Build Glad (loader)
add_library(glad STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c
)
target_include_directories(glad PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
)

# GLM (header-only)
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
)

# Source files
file(GLOB_RECURSE TRIDENT_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)

# Engine core library
add_library(Trident STATIC ${TRIDENT_SOURCES})

# Precompiled header setup
target_precompile_headers(Trident PRIVATE src/Core.h)

# Include paths
target_include_directories(Trident PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ImGui
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui")

file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(ImGui STATIC ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)

# Replaced GL with opengl32
target_link_libraries(ImGui PUBLIC glfw opengl32)

# Trident engine links
target_link_libraries(Trident PUBLIC
    glad
    glfw
    glm
    opengl32
    ImGui
)

# MSVC-specific object output location
target_compile_options(Trident PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/Fo"${CMAKE_SOURCE_DIR}/bin-int/${OUTPUT_DIR}/Trident/">
)