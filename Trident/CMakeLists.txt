project(Trident)

# Build Glad (loader) from your vendor folder
add_library(glad STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c
)
target_include_directories(glad PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
)

file(GLOB_RECURSE TRIDENT_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)

# Engine core
add_library(Trident STATIC ${TRIDENT_SOURCES})

# Precompiled header setup
target_precompile_headers(Trident PRIVATE src/Core/Core.h)

target_include_directories(Trident PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link against Glad, GLFW and the system OpenGL
target_link_libraries(Trident
    PUBLIC
      glad
      glfw
      opengl32    # on Windows
)

# Redirect .obj’s into bin-int/…/Trident when building with MSVC
target_compile_options(Trident PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/Fo"${CMAKE_SOURCE_DIR}/bin-int/${OUTPUT_DIR}/Trident/">
)