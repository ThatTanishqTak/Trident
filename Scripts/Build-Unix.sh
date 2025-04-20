#!/bin/bash

echo "======================================="
echo "   Starting Trident Build (Unix)"
echo "======================================="

# Prompt for build type
read -p "Enter build type (Debug/Release): " BUILD_TYPE

# Normalize input
BUILD_TYPE=$(echo "$BUILD_TYPE" | tr '[:lower:]' '[:upper:]')
if [[ "$BUILD_TYPE" != "DEBUG" && "$BUILD_TYPE" != "RELEASE" ]]; then
    echo "Invalid build type. Defaulting to Debug."
    BUILD_TYPE="Debug"
else
    BUILD_TYPE="$(tr '[:upper:]' '[:lower:]' <<< ${BUILD_TYPE:0:1})${BUILD_TYPE:1}"
fi

# Move to root directory
cd "$(dirname "$0")/.." || exit

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

cd build || exit

# Run CMake configuration
echo "Configuring project with CMake ($BUILD_TYPE)..."
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

# Build the project
echo "Building project..."
cmake --build . --config $BUILD_TYPE

echo "======================================="
echo "     Build finished ($BUILD_TYPE)"
echo "======================================="