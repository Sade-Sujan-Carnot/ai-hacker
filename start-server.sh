#!/bin/bash
# For Linux/Mac deployment

PORT=${PORT:-8080}
cd backend/build || mkdir -p backend/build
cd backend/build
cmake .. || exit 1
cmake --build . --config Release || exit 1
./weather_server
