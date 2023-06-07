#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "bald balaji";     
const char* password = "hotspoyt";  



ESP8266WebServer server(80);  

void handleRoot() {
  if (server.method() == HTTP_POST) {
    String message = server.arg("plain");
    Serial.println(message);
  }
  server.send(200, "text/html", "<h1>Hello from ESP8266!</h1>");
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());

  server.on("/", handleRoot);

  server.begin();
  Serial.println("Web server started");




}

void loop() {
  server.handleClient();
}
