# Weather Backend Setup - FREE API Edition

## ✨ NO API KEY REQUIRED!

This backend uses **Open-Meteo**, a completely free weather API with no authentication needed.

## Prerequisites
1. Visual Studio 2019 or later (with C++ development tools)
2. CMake 3.10 or later
3. CURL and jsoncpp libraries

## Installation on Windows

### 1. Install vcpkg (Package Manager)
```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\vcpkg\integrate install
```

### 2. Install Required Libraries
```bash
.\vcpkg install curl:x64-windows
.\vcpkg install jsoncpp:x64-windows
```

### 3. Build the Project
```bash
cd backend
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake -A x64
cmake --build . --config Release
```

### 4. Run the Server
```bash
Release\weather_server.exe
```

The server will start on `http://localhost:8080`

## Quick Start
1. Compile the C++ code (no configuration needed!)
2. Run the executable
3. Visit `http://localhost:8080` to see API info
4. API data updates in real-time from Open-Meteo

## API Endpoints

### GET /weather
Returns real-time weather data for Hyderabad

**Response:**
```json
{
  "city": "Hyderabad",
  "country": "IN",
  "temperature": 28.5,
  "feelsLike": 29.2,
  "humidity": 65,
  "windSpeed": 3.2,
  "pressure": 1013,
  "description": "clear sky",
  "icon": "Clear",
  "visibility": 10.0,
  "cloudiness": 40,
  "latitude": 17.3850,
  "longitude": 78.4867
}
```

### GET /
Returns HTML dashboard with API documentation

## About Open-Meteo

- ✅ **100% FREE** - No registration or API key required
- ✅ **No Rate Limits** - Unlimited free requests
- ✅ **High Accuracy** - Professional weather data
- ✅ **Fast** - Global CDN infrastructure
- ✅ **Open Source** - Transparent and reliable

[Learn more about Open-Meteo](https://open-meteo.com)

## Troubleshooting
- If CMake can't find packages, update the CMakeLists.txt with full paths
- Ensure Windows Defender doesn't block the server port
- Check firewall settings for port 8080
- Run as Administrator if port binding fails

