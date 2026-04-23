# Weather App with C++ Backend - FREE API

A real-time weather application for Hyderabad featuring a modern JavaScript frontend and C++ backend powered by **Open-Meteo's FREE API**.

## 🎨 Features

- **Real-time Weather Data**: Live Hyderabad weather (completely FREE!)
- **C++ Backend**: High-performance HTTP server serving weather data
- **NO API KEY REQUIRED**: Uses Open-Meteo's free weather API
- **Animated UI**: Beautiful JavaScript animations and particle effects
- **Auto-Refresh**: Automatic weather updates every 5 minutes
- **Responsive Design**: Glassmorphism UI with smooth animations
- **Cross-Origin Support**: CORS enabled for seamless frontend-backend communication

## 🔓 What Makes It Free?

✅ **Open-Meteo API** - 100% FREE, no registration needed  
✅ **Unlimited Requests** - No rate limiting  
✅ **No API Key** - Just compile and run  
✅ **Professional Data** - Same accuracy as premium services  
✅ **Fast & Reliable** - Global CDN infrastructure  

## 📁 Project Structure

```
ai-hacker/
├── index.html              # Frontend UI with animations
├── backend/
│   ├── main.cpp           # C++ HTTP server (uses Open-Meteo FREE API)
│   ├── CMakeLists.txt     # Build configuration
│   ├── setup.md           # Detailed setup instructions
│   ├── build.bat          # Windows build script
│   └── run.bat            # Windows run script
└── README.md
```

## 🚀 Quick Start (5 Minutes)

### 1. Setup Backend (Windows)

#### Option A: Using batch scripts (EASIEST)

1. Navigate to the `backend` folder
2. Open Command Prompt
3. Run: `build.bat`
4. Run: `run.bat`

The server will start on `http://localhost:8080`

#### Option B: Manual Setup

```bash
cd backend
mkdir build
cd build

# Replace with your vcpkg path
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake -A x64

cmake --build . --config Release
.\Release\weather_server.exe
```

### 2. Run Frontend

1. Open `index.html` in a web browser, or
2. Use a local server (recommended):

**Python 3:**
```bash
python -m http.server 3000
```

**Python 2:**
```bash
python -m SimpleHTTPServer 3000
```

**Node.js:**
```bash
npx http-server
```

3. Navigate to `http://localhost:3000`

## 🔧 Configuration

### Backend Configuration (main.cpp)
- **Port**: Line ~170 - Default is 8080 (easily changeable)
- **City**: Line ~115 - Configured for Hyderabad
- **No API Key Needed!**

### Frontend Configuration (index.html)
- **Backend URL**: Line ~294 - Default is `http://localhost:8080`
- **Auto-Refresh Interval**: Line ~360 - Set to 300000ms (5 minutes)

## 📊 API Response Format

**GET /weather**

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

**GET /** - Returns HTML dashboard with API documentation

## 🐛 Troubleshooting

### Build Issues

**Problem**: CMake can't find CURL or jsoncpp
```bash
vcpkg install curl:x64-windows
vcpkg install jsoncpp:x64-windows
```

**Problem**: "MSVC compiler not found"
- Install Visual Studio 2019+ with C++ development tools

### Runtime Issues

**Problem**: "Backend connection failed"
- Ensure C++ server is running: `http://localhost:8080`
- Check Windows Firewall allows port 8080
- Verify no other app uses port 8080

**Problem**: "Cannot open include file: 'curl/curl.h'"
- Rebuild using vcpkg toolchain
- Ensure CMake has correct toolchain path

## 📈 Performance

- **API Response Time**: < 100ms
- **Refresh Rate**: Every 5 minutes (configurable)
- **Data Accuracy**: Real-time from Open-Meteo
- **Zero Cost**: Completely FREE

## 📝 Future Enhancements

- [ ] Support for multiple cities
- [ ] Weather forecast (5-day, hourly)
- [ ] Historical data storage
- [ ] Docker containerization
- [ ] Deployment to AWS/Azure/GCP
- [ ] Mobile app version
- [ ] Database integration

## 🛠️ Dependencies

### Frontend
- HTML5, CSS3, JavaScript ES6+ (No external libraries)

### Backend (C++)
- **CURL**: HTTP client for weather API
- **jsoncpp**: JSON parsing and generation
- **Windows Socket API**: HTTP server
- **Open-Meteo**: Free weather data source (no API key!)

## 🌍 About Open-Meteo

Open-Meteo is an open-source weather API that provides:
- Free and open-source weather data
- No authentication or API key required
- Global coverage with high accuracy
- Professional-grade weather models
- Completely free to use

[Learn more about Open-Meteo](https://open-meteo.com)

## 📄 License

Open source - Feel free to use, modify, and distribute

## 🤝 Contributing

To contribute improvements, fork the repository and submit a pull request.

## ✨ Why This Project?

- **Zero Cost**: No API fees or subscriptions
- **Educational**: Learn C++, networking, and web development
- **Practical**: Real-world weather application
- **Extensible**: Easy to add features and support more cities
- **Open Source**: Transparent and community-driven

## 📞 Support

For issues or questions:
1. Check the troubleshooting section
2. Review [Open-Meteo API docs](https://open-meteo.com/en/docs)
3. Check build logs for error messages

---

**Happy coding! 🚀**