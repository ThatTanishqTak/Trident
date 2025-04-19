project(Forge)

add_executable(Forge
    src/EntryPoint.cpp
)

# Make sure Forge can find the engine headers
target_include_directories(Forge PRIVATE
    ${CMAKE_SOURCE_DIR}/Trident/src
)

# Link Forge against Trident (and transitively GLFW/Glad)
target_link_libraries(Forge PRIVATE
    Trident
)

# Put the .exe into bin/… and .obj’s into bin-int/…/Forge
target_compile_options(Forge PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/Fo"${CMAKE_SOURCE_DIR}/bin-int/${OUTPUT_DIR}/Forge/">
)
set_target_properties(Forge PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY   ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY   ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY   ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}
)