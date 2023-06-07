#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "bald balaji";
const char* password = "hotspoyt";

const int motor1PinIN1 = 0;
const int motor1PinIN2 = 3; //check
const int motor1PinEn = 2;

const int motor2PinIN1 = 4; // Check- to be changed
const int motor2PinIN2 = 5; // check
const int motor2PinEn = 8;

ESP8266WebServer server(80);

void handleRoot() {
  if (server.method() == HTTP_POST) {
    String message = server.arg("plain");
    Serial.println(message);

    if (message == "forward") {
      digitalWrite(motor1PinIN1, HIGH);
      digitalWrite(motor1PinIN2, LOW);
      digitalWrite(motor2PinIN1, HIGH);
      digitalWrite(motor2PinIN2, LOW);
    } else if (message == "backward") {
      digitalWrite(motor1PinIN1, LOW);
      digitalWrite(motor1PinIN2, HIGH);
      digitalWrite(motor2PinIN1, LOW);
      digitalWrite(motor2PinIN2, HIGH);
    } else if (message == "left") {
      digitalWrite(motor1PinIN1, LOW);
      digitalWrite(motor1PinIN2, HIGH);
      digitalWrite(motor2PinIN1, HIGH);
      digitalWrite(motor2PinIN2, LOW);
    } else if (message == "right") {
      digitalWrite(motor1PinIN1, HIGH);
      digitalWrite(motor1PinIN2, LOW);
      digitalWrite(motor2PinIN1, LOW);
      digitalWrite(motor2PinIN2, HIGH);
    } else if (message == "stop") {
      digitalWrite(motor1PinIN1, LOW);
      digitalWrite(motor1PinIN2, LOW);
      digitalWrite(motor2PinIN1, LOW);
      digitalWrite(motor2PinIN2, LOW);
    }
  }

  delay(5000);
  server.send(200, "text/html", "<h1>Hello from ESP8266!</h1>");
}

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());

  pinMode(motor1PinIN1, OUTPUT);
  pinMode(motor1PinIN2, OUTPUT);
  pinMode(motor2PinIN1, OUTPUT);
  pinMode(motor2PinIN2, OUTPUT);

  

  server.on("/", handleRoot);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient(); // Handle incoming client requests
}
