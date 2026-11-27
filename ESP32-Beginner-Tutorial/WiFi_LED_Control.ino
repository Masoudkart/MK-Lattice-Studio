#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_PASSWORD";

const int ledPin = 4;

WebServer server(80);

void handleRoot() {
  String page = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <title>ESP32 LED Control</title>
    </head>
    <body style="text-align:center; font-family:Arial;">
      <h2>ESP32 LED Control</h2>
      <p><a href="/on"><button style="font-size:25px;">ON</button></a></p>
      <p><a href="/off"><button style="font-size:25px;">OFF</button></a></p>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.on("/on", []() {
    digitalWrite(ledPin, HIGH);
    handleRoot();
  });

  server.on("/off", []() {
    digitalWrite(ledPin, LOW);
    handleRoot();
  });

  server.begin();
  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();
}
