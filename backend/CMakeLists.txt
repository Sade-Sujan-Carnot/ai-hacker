cmake_minimum_required(VERSION 3.10)
project(WeatherBackend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(CURL REQUIRED)
find_package(jsoncpp REQUIRED)

# Add executable
add_executable(weather_server main.cpp)

# Link libraries
target_link_libraries(weather_server 
    CURL::libcurl
    jsoncpp
    ws2_32
)

# For Windows
if(WIN32)
    target_link_libraries(weather_server ws2_32 wsock32)
endif()
