@echo off
REM Weather Backend Build Script for Windows

echo ===================================
echo Weather Backend - Build Script
echo ===================================
echo.

REM Check if CURL and jsoncpp are installed via vcpkg
if not exist "%VCPKG_ROOT%\vcpkg.exe" (
    echo ERROR: vcpkg not found!
    echo Please install vcpkg first: https://github.com/Microsoft/vcpkg
    echo.
    echo Instructions:
    echo 1. git clone https://github.com/Microsoft/vcpkg.git
    echo 2. cd vcpkg
    echo 3. .\bootstrap-vcpkg.bat
    echo 4. .\vcpkg integrate install
    echo 5. Set VCPKG_ROOT environment variable to vcpkg folder
    pause
    exit /b 1
)

echo Installing required packages via vcpkg...
call "%VCPKG_ROOT%\vcpkg" install curl:x64-windows
call "%VCPKG_ROOT%\vcpkg" install jsoncpp:x64-windows

echo.
echo Creating build directory...
if not exist build mkdir build
cd build

echo.
echo Running CMake...
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -A x64

echo.
echo Building project...
cmake --build . --config Release

echo.
echo Build complete!
echo.
echo To run the server:
echo   .\Release\weather_server.exe
echo.
pause
