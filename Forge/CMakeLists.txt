project(Forge)

# Detect and set output directory variables
set(OS_NAME ${CMAKE_SYSTEM_NAME})

# Normalize arch name: x86, x64, arm, etc.
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH x64)
else()
    set(ARCH x86)
endif()

# Output directory pattern: eg:- Windows-Debug-x64
set(OUTPUT_DIR "${OS_NAME}-$<CONFIG>-${ARCH}")

# Recursively collect all .cpp and .h files in src/
file(GLOB_RECURSE FORGE_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)

# Create Forge executable based on build type
# Only add WIN32 for Release on MSVC
if (MSVC)
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        add_executable(Forge WIN32 ${FORGE_SOURCES})
    else()
        add_executable(Forge ${FORGE_SOURCES})
    endif()
else()
    add_executable(Forge ${FORGE_SOURCES})
endif()

# Include Trident engine headers
target_include_directories(Forge PRIVATE ${CMAKE_SOURCE_DIR}/Trident/src)

# Link to Trident engine
target_link_libraries(Forge PRIVATE Trident)

# Apply release-only linker flags for GUI entry point
if (MSVC)
    set_target_properties(Forge PROPERTIES
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()

# Object file output location (MSVC only)
target_compile_options(Forge PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/Fo"${CMAKE_SOURCE_DIR}/bin-int/${OUTPUT_DIR}/Forge/">
)

# Executable + Library output folders
set_target_properties(Forge PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}
)

# Copy Shaders directory to output binary directory
add_custom_command(TARGET Forge POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Forge/Shaders"
    "$<TARGET_FILE_DIR:Forge>/Shaders")