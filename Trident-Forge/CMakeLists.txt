### Trident-Forge Project ###

# Set the project name for the Forge editor
project(Trident-Forge)

# Redefine output directory variables
set(OS_NAME ${CMAKE_SYSTEM_NAME})
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH x64)
else()
    set(ARCH x86)
endif()
set(OUTPUT_DIR "${OS_NAME}-$<CONFIG>-${ARCH}")

# Collect all source files for Forge
file(GLOB_RECURSE Trident-Forge_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)

# Create Forge executable (use WIN32 for GUI entry point on MSVC/Release)
if (MSVC)
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        add_executable(Trident-Forge WIN32 ${Trident-Forge_SOURCES})
    else()
        add_executable(Trident-Forge ${Trident-Forge_SOURCES})
    endif()
else()
    add_executable(Trident-Forge ${Trident-Forge_SOURCES})
endif()

# Include Trident headers
target_include_directories(Trident-Forge PRIVATE ${CMAKE_SOURCE_DIR}/Trident/src)

# Link against Trident engine
target_link_libraries(Trident-Forge PRIVATE Trident)

# Set linker flags for Release GUI apps on Windows (no console)
if (MSVC)
    set_target_properties(Trident-Forge PROPERTIES
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()

# MSVC-specific object file directory for Forge
target_compile_options(Trident-Forge PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/Fo"${CMAKE_SOURCE_DIR}/bin-int/${OUTPUT_DIR}/Trident-Forge/">
)

# Set binary output paths for Forge
set_target_properties(Trident-Forge PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR}
)

# Copy assets after build to the output directory
add_custom_command(TARGET Trident-Forge POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Trident-Forge/Assets"
    "$<TARGET_FILE_DIR:Trident-Forge>/Assets"
)