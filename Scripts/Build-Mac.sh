echo "======================================"
echo "Starting Trident Build (macOS)"
echo "======================================"

# Ask user for build type
read -p "Enter build type (Debug/Release): " BUILD_TYPE

# Default to Debug if input is invalid
if [[ "$BUILD_TYPE" != "Debug" && "$BUILD_TYPE" != "Release" ]]; then
  echo "Invalid build type. Defaulting to Debug."
  BUILD_TYPE="Debug"
fi

# Move to root directory
cd "$(dirname "$0")/.."

# Create build folder if it doesn't exist
mkdir -p build
cd build

# Configure with CMake
echo "Configuring project with CMake ($BUILD_TYPE)..."
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

# Build project
echo "Building project..."
cmake --build . --config $BUILD_TYPE

echo "======================================"
echo "Build finished ($BUILD_TYPE)."
echo "======================================"