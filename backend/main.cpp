#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <string>
#include <thread>
#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iomanip>
#include <sstream>
#include <cmath>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libcurl.lib")

// Callback for CURL to write response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    s->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Fetch weather data from Open-Meteo FREE API (no API key required!)
std::string fetchWeatherData(double latitude, double longitude) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    
    if (curl) {
        // Open-Meteo: Free weather API - no authentication needed!
        // Hyderabad coordinates: 17.3850, 78.4867
        std::string url = "https://api.open-meteo.com/v1/forecast?latitude=" + 
                         std::to_string(latitude) + "&longitude=" + std::to_string(longitude) +
                         "&current=temperature_2m,relative_humidity_2m,apparent_temperature,weather_code,wind_speed_10m,pressure_msl,cloud_cover&timezone=Asia/Kolkata";
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        
        CURLcode res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        
        curl_easy_cleanup(curl);
    }
    
    return readBuffer;
}

// WMO Weather Code to description mapping
std::string getWeatherDescription(int code) {
    switch(code) {
        case 0: return "clear sky";
        case 1: case 2: return "mostly clear";
        case 3: return "overcast";
        case 45: case 48: return "foggy";
        case 51: case 53: case 55: return "light drizzle";
        case 61: case 63: case 65: return "rain";
        case 71: case 73: case 75: return "snow";
        case 77: return "snow grains";
        case 80: case 81: case 82: return "rain showers";
        case 85: case 86: return "snow showers";
        case 95: case 96: case 99: return "thunderstorm";
        default: return "unknown";
    }
}

// Parse JSON from Open-Meteo and create response
std::string formatWeatherResponse(const std::string& jsonData) {
    Json::CharReaderBuilder reader;
    Json::Value obj;
    std::string errs;
    
    std::istringstream s(jsonData);
    if (!Json::parseFromStream(reader, s, &obj, &errs)) {
        return "{\"error\": \"Failed to parse JSON\"}";
    }
    
    if (!obj.isMember("current")) {
        return "{\"error\": \"Invalid API response\"}";
    }
    
    Json::Value current = obj["current"];
    int weatherCode = current["weather_code"].asInt();
    
    Json::Value response;
    response["city"] = "Hyderabad";
    response["country"] = "IN";
    response["temperature"] = current["temperature_2m"].asDouble();
    response["feelsLike"] = current["apparent_temperature"].asDouble();
    response["humidity"] = current["relative_humidity_2m"].asInt();
    response["windSpeed"] = current["wind_speed_10m"].asDouble();
    response["pressure"] = current["pressure_msl"].asInt();
    response["description"] = getWeatherDescription(weatherCode);
    
    // Map WMO code to icon
    if (weatherCode == 0) response["icon"] = "Clear";
    else if (weatherCode <= 3) response["icon"] = "PartlyCloudy";
    else if (weatherCode <= 48) response["icon"] = "Cloudy";
    else if (weatherCode <= 67) response["icon"] = "Rain";
    else if (weatherCode <= 86) response["icon"] = "Snow";
    else response["icon"] = "Thunderstorm";
    
    response["visibility"] = 10.0;
    response["cloudiness"] = current["cloud_cover"].asInt();
    response["latitude"] = 17.3850;
    response["longitude"] = 78.4867;
    
    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, response);
}

// Simple HTTP server implementation
void runHttpServer(int port) {
    WSADATA wsaData;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET clientSocket = INVALID_SOCKET;
    
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        return;
    }
    
    struct addrinfo *result = nullptr, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    
    iResult = getaddrinfo(nullptr, std::to_string(port).c_str(), &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed: " << iResult << std::endl;
        WSACleanup();
        return;
    }
    
    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "socket failed" << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return;
    }
    
    iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "bind failed" << std::endl;
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return;
    }
    
    freeaddrinfo(result);
    
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "listen failed" << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return;
    }
    
    std::cout << "======================================" << std::endl;
    std::cout << "🌦️  WEATHER API SERVER - FREE EDITION" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "Server listening on port " << port << "..." << std::endl;
    std::cout << "API: Open-Meteo (NO API KEY NEEDED!)" << std::endl;
    std::cout << "Endpoint: http://localhost:" << port << "/weather" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << std::endl;
    
    while (true) {
        clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "accept failed" << std::endl;
            continue;
        }
        
        char recvbuf[512] = {0};
        int iResult = recv(clientSocket, recvbuf, sizeof(recvbuf), 0);
        
        if (iResult > 0) {
            std::string request(recvbuf);
            std::string response;
            
            if (request.find("GET /weather") != std::string::npos) {
                // Hyderabad coordinates: 17.3850°N, 78.4867°E
                std::string weatherData = fetchWeatherData(17.3850, 78.4867);
                std::string formattedData = formatWeatherResponse(weatherData);
                
                std::cout << "[" << std::chrono::system_clock::now().time_since_epoch().count() % 100000 
                          << "] Weather request received - Hyderabad data fetched" << std::endl;
                
                response = "HTTP/1.1 200 OK\r\n";
                response += "Content-Type: application/json\r\n";
                response += "Access-Control-Allow-Origin: *\r\n";
                response += "Connection: close\r\n";
                response += "Content-Length: " + std::to_string(formattedData.length()) + "\r\n";
                response += "\r\n";
                response += formattedData;
            } else if (request.find("GET /") != std::string::npos) {
                std::string htmlResponse = R"(
<!DOCTYPE html>
<html>
<head>
    <title>Weather API - Free Edition</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; background: #f0f0f0; }
        h1 { color: #333; }
        .info { background: #fff; padding: 20px; border-radius: 5px; box-shadow: 0 2px 5px rgba(0,0,0,0.1); }
        .endpoint { background: #e8f4f8; padding: 10px; border-left: 4px solid #2196F3; margin: 10px 0; }
        code { background: #f5f5f5; padding: 2px 5px; border-radius: 3px; }
        .free-badge { background: #4CAF50; color: white; padding: 5px 10px; border-radius: 3px; display: inline-block; margin: 10px 0; }
    </style>
</head>
<body>
    <h1>🌦️ Weather API - Free Edition</h1>
    <div class="info">
        <p><strong>Welcome to the FREE Weather API!</strong></p>
        <div class="free-badge">✓ 100% FREE - No API Key Required!</div>
        
        <h2>API Endpoints</h2>
        
        <h3>Get Weather for Hyderabad</h3>
        <div class="endpoint">
            <strong>Endpoint:</strong> <code>GET /weather</code><br>
            <strong>Base URL:</strong> <code>http://localhost:8080</code><br>
            <strong>Response Format:</strong> JSON
        </div>
        
        <h2>Example Response</h2>
        <pre style="background: #f5f5f5; padding: 10px; border-radius: 3px; overflow-x: auto;">{
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
  "cloudiness": 20,
  "latitude": 17.3850,
  "longitude": 78.4867
}</pre>
        
        <h2>Features</h2>
        <ul>
            <li>✓ Real-time weather data for Hyderabad</li>
            <li>✓ Powered by Open-Meteo (Free, No Authentication)</li>
            <li>✓ CORS enabled for web integration</li>
            <li>✓ JSON responses</li>
            <li>✓ Fast and reliable</li>
        </ul>
        
        <h2>Data Points</h2>
        <ul>
            <li>Temperature (°C)</li>
            <li>Feels Like Temperature</li>
            <li>Humidity (%)</li>
            <li>Wind Speed (m/s)</li>
            <li>Pressure (hPa)</li>
            <li>Weather Description</li>
            <li>Cloud Cover (%)</li>
            <li>And more...</li>
        </ul>
        
        <h2>Usage Example</h2>
        <pre style="background: #f5f5f5; padding: 10px; border-radius: 3px; overflow-x: auto;">
// JavaScript
fetch('http://localhost:8080/weather')
  .then(response => response.json())
  .then(data => console.log(data));</pre>
        
        <h2>About</h2>
        <p>This API uses <strong>Open-Meteo</strong>, a free weather API that requires no authentication.</p>
        <p><a href="https://open-meteo.com" target="_blank">Learn more about Open-Meteo</a></p>
    </div>
</body>
</html>
)";
                
                response = "HTTP/1.1 200 OK\r\n";
                response += "Content-Type: text/html\r\n";
                response += "Access-Control-Allow-Origin: *\r\n";
                response += "Connection: close\r\n";
                response += "Content-Length: " + std::to_string(htmlResponse.length()) + "\r\n";
                response += "\r\n";
                response += htmlResponse;
            } else if (request.find("OPTIONS") != std::string::npos) {
                response = "HTTP/1.1 200 OK\r\n";
                response += "Access-Control-Allow-Origin: *\r\n";
                response += "Access-Control-Allow-Methods: GET, OPTIONS\r\n";
                response += "Access-Control-Allow-Headers: Content-Type\r\n";
                response += "Connection: close\r\n";
                response += "\r\n";
            } else {
                response = "HTTP/1.1 404 Not Found\r\n";
                response += "Content-Type: text/plain\r\n";
                response += "Connection: close\r\n";
                response += "\r\n";
                response += "404 Not Found";
            }
            
            send(clientSocket, response.c_str(), (int)response.length(), 0);
        }
        
        closesocket(clientSocket);
    }
    
    closesocket(listenSocket);
    WSACleanup();
}

int main() {
    int port = 8080;
    
    std::cout << std::endl;
    std::cout << "Starting Weather API Server..." << std::endl;
    std::cout << std::endl;
    
    runHttpServer(port);
    
    return 0;
}
