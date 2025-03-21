# ESP32-CAM Web Server 📷

This project sets up an ESP32-CAM as a web server that captures and serves images via HTTP.

## 📌 Features
- Captures images from the ESP32-CAM
- Serves images via a web interface
- Supports flash control via URL parameters

## 📂 Project Structure
```
.
├── README.md
├── lib
│   └── esp32cam-main.zip (https://github.com/yoursunny/esp32cam)
└── src
    └── main.ino
```

## 🚀 Getting Started
### Prerequisites
Ensure you have the following installed:
- [Arduino IDE](https://www.arduino.cc/en/software)
- ESP32 board support (Install via Arduino Board Manager)
- Required libraries (WiFi, WebServer, esp32cam)

### 🔧 Setup Instructions
1. Open `main.ino` in Arduino IDE.
2. Replace the Wi-Fi credentials in the following lines:
   ```cpp
   const char *WIFI_SSID = "YOUR_WIFI_SSID";
   const char *WIFI_PASS = "YOUR_WIFI_PASSWORD";
   ```
3. Select **AI Thinker ESP32-CAM** as the board.
4. Connect the ESP32-CAM and upload the code.

### 📡 Accessing the Web Server
After uploading, check the serial monitor for the assigned IP address. Use a web browser or API tool to request images.

## 🌐 API Endpoints
| Endpoint         | Method | Parameters            | Description               |
|-----------------|--------|----------------------|---------------------------|
| `/frame.jpg`    | GET    | `flash=true/false`  | Captures and returns an image. Default `flash=false`. |

### Example Request
```
http://<ESP32-CAM-IP>/frame.jpg?flash=true
```

## 🛠 Troubleshooting
- If the camera fails to initialize, check the wiring and power supply.
- If the ESP32-CAM does not connect to Wi-Fi, verify SSID and password.
- If necessary, install [esp32cam](https://github.com/yoursunny/esp32cam) in your Arduino IDE.

## 📖 Additional Resources
For a step-by-step guide on setting up the ESP32-CAM with Arduino IDE, refer to this tutorial:
🔗 [ESP32-CAM Setup Guide](https://www.usinainfo.com.br/blog/programando-esp32-cam-wifi-com-esp32-cam-mb/?srsltid=AfmBOoo6XoE8NmsuhhmdC9CI06Q8Ww8W3rly1uewNH0_Epc8pb4Sepsn)