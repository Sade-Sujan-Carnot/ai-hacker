@echo off
REM Weather Backend Run Script

echo ===================================
echo Weather Backend - Server
echo ===================================
echo.
echo Starting server on http://localhost:8080
echo.
echo Press Ctrl+C to stop the server
echo.

if exist "build\Release\weather_server.exe" (
    "build\Release\weather_server.exe"
) else (
    echo ERROR: weather_server.exe not found!
    echo Please run build.bat first to compile the project
    pause
    exit /b 1
)
