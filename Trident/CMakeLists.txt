project(Trident)

# Build Glad (loader) from your vendor folder
add_library(glad STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c
)
target_include_directories(glad PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
)

# Add GLM (header-only)
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
)

# Collect all source files
file(GLOB_RECURSE TRIDENT_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)

# Define Trident as a SHARED library (DLL)
add_library(Trident SHARED ${TRIDENT_SOURCES})

# Enable DLL export macro in code
target_compile_definitions(Trident PRIVATE TRIDENT_BUILD_DLL)

# Precompiled header setup
target_precompile_headers(Trident PRIVATE src/Core.h)

# Include engine headers
target_include_directories(Trident PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link against dependencies
target_link_libraries(Trident PUBLIC
    glad
    glfw
    glm
    opengl32  # on Windows
)

# Redirect .obj files into bin-int/.../Trident when building with MSVC
target_compile_options(Trident PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/Fo"${CMAKE_SOURCE_DIR}/bin-int/${OUTPUT_DIR}/Trident/">
)