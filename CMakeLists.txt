cmake_minimum_required(VERSION 3.20)
project(Trident)

set(CMAKE_CXX_STANDARD 20)

# Figure out config name (Debug/Release) for multi‑config generators
get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(IS_MULTI_CONFIG)
  set(OUTPUT_CONFIG "$<CONFIG>")
else()
  set(OUTPUT_CONFIG "${CMAKE_BUILD_TYPE}")
endif()

# Build‐folder naming: e.g. windows-Debug-amd64
string(TOLOWER ${CMAKE_SYSTEM_NAME} OS_NAME)
string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} ARCH)
set(OUTPUT_DIR "${OS_NAME}-${OUTPUT_CONFIG}-${ARCH}")

# Final binary output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}")

# Disable GLFW examples/tests in vendor
set(GLFW_BUILD_DOCS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS   OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Pull in GLFW
add_subdirectory(${CMAKE_SOURCE_DIR}/Trident/vendor/glfw)

# Pull in your two projects
add_subdirectory(Trident)
add_subdirectory(Forge)