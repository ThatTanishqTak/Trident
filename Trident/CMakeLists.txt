### Trident Project ###

# Set the project again for Trident engine (can be omitted unless needed for IDE grouping)
project(Trident)

# Add Glad OpenGL loader as a static library
add_library(glad STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c
)
target_include_directories(glad PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
)

# Add GLM
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
)

# Add EnTT 
add_library(entt INTERFACE)
target_include_directories(entt INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/entt/src
)

# Gather all source and header files from the engine
file(GLOB_RECURSE TRIDENT_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)

# Define Trident engine as a static library
add_library(Trident STATIC ${TRIDENT_SOURCES})

# Use precompiled headers for faster compilation
target_precompile_headers(Trident PRIVATE src/Core.h)

# Include path for Trident engine
target_include_directories(Trident PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add ImGui as a static library
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui")
file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(ImGui STATIC ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)
target_link_libraries(ImGui PUBLIC glfw opengl32)

# Link Trident with dependencies
target_link_libraries(Trident PUBLIC
    glad
    glfw
    glm
    entt
    opengl32
    ImGui
)

# Set MSVC-specific object file output directory
target_compile_options(Trident PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/Fo"${CMAKE_SOURCE_DIR}/bin-int/${OUTPUT_DIR}/Trident/">
)