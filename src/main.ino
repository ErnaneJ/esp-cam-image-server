/**
 * @file main.cpp
 * @brief ESP32-CAM Web Server to serve captured images from the camera.
 */

#include <WebServer.h>
#include <WiFi.h>
#include <esp32cam.h>

// WiFi credentials
const char *WIFI_SSID = "**********";
const char *WIFI_PASS = "**********";

WebServer server(80);

const int ledPin = 4;

// Default resolution for image capture
static auto resolution = esp32cam::Resolution::find(800, 600);

/**
 * @brief Function to handle the request to capture and send a JPEG image.
 */
void handle_jpg()
{
  Serial.println("Handling request...");

  if (server.hasArg("flash"))
  {
    String flashParam = server.arg("flash");

    if (flashParam.equalsIgnoreCase("true"))
    {
      digitalWrite(ledPin, HIGH);
      Serial.println("Flash on");
    }
    else
    {
      digitalWrite(ledPin, LOW);
      Serial.println("Flash off");
    }
  }
  else
  {
    digitalWrite(ledPin, LOW);
    Serial.println("Flash off (default)");
  }

  Serial.println("Capturing frame...");
  auto frame = esp32cam::capture();
  if (frame == nullptr)
  {
    Serial.println("Failed to capture frame");
    server.send(503, "", "");
    return;
  }

  Serial.printf("Capture successful: %dx%d, size: %d bytes\n", frame->getWidth(), frame->getHeight(),
                static_cast<int>(frame->size()));

  if (!frame->isJpeg())
  {
    if (!frame->toJpeg(80)) // JPEG quality of 80%
    {
      Serial.println("Failed to convert to JPEG");
      server.send(503, "", "");
      return;
    }
  }

  // Serve the JPEG image
  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
  Serial.println("JPEG served successfully");
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  pinMode(ledPin, OUTPUT);  
  digitalWrite(ledPin, LOW);

  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(Resolution::find(800, 600)); // Initial resolution setting
    cfg.setBufferCount(2);
    cfg.setJpeg(80);

    bool camera_ok = Camera.begin(cfg);
    Serial.println(camera_ok ? "Camera initialized" : "Failed to initialize camera");
  }

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");

  Serial.println("Routes:");
  Serial.println("- http://" + WiFi.localIP().toString() + "/frame.jpg");
  Serial.println("Params:");
  Serial.println("- flash: true|false (default: false)");

  server.on("/frame.jpg", handle_jpg);

  server.begin();
}

void loop()
{
  server.handleClient();
}
