@echo off
echo ======================================
echo Starting Trident Build (Windows)
echo ======================================

:: Ask user for build type
set BUILD_TYPE=
set /P BUILD_TYPE="Enter build type (Debug/Release): "

:: Convert to uppercase for safety
set "BUILD_TYPE=%BUILD_TYPE:~0,1%%BUILD_TYPE:~1%"
if /I "%BUILD_TYPE%"=="Debug" (
    set BUILD_TYPE=Debug
) else if /I "%BUILD_TYPE%"=="Release" (
    set BUILD_TYPE=Release
) else (
    echo Invalid build type. Defaulting to Debug.
    set BUILD_TYPE=Debug
)

:: Move to root directory
cd ..

:: Create build folder if it doesn't exist
if not exist build (
    echo Creating build directory...
    mkdir build
)

cd build

:: Run CMake configuration
echo Configuring project with CMake (%BUILD_TYPE%)...
cmake -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ..

:: Build the project
echo Building project...
cmake --build . --config %BUILD_TYPE%

echo ======================================
echo Build finished (%BUILD_TYPE%).
echo ======================================

pause