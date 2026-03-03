/*
This program sets up a simple web server on an ESP8266.
It allows users to control the built-in LED (GPIO2) through a web interface.
Clicking the 'LED ON' button turns on the LED, while 'LED OFF' turns it off.
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your Wi-Fi credentials
const char* ssid = "Wifi_Name";
const char* password = "Wifi_pass";

ESP8266WebServer server(80); // Web server on port 80

const int ledPin = 2; // Built-in LED pin (GPIO2 for ESP8266)
bool ledState = false; // Track LED state

// HTML content for the web page
String HTMLPage() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><title>ESP8266 LED Control</title></head>";
  html += "<body style='text-align: center; font-family: Arial;'>";
  
  html += "<h1>ESP8266 LED Control</h1>";
  html += ledState ? "<p>LED is <strong>ON</strong></p>" : "<p>LED is <strong>OFF</strong></p>";
  html += "<a href='/on' style='padding: 10px 20px; background-color: green; color: white; text-decoration: none;'>Turn ON</a>&nbsp;";
  html += "<a href='/off' style='padding: 10px 20px; background-color: red; color: white; text-decoration: none;'>Turn OFF</a>";
  
  html += "</body></html>";
  return html;
}

// Handle the root path "/"
void handleRoot() {
  server.send(200, "text/html", HTMLPage());
}

// Handle LED ON request
void handleLEDOn() {
  ledState = true;
  digitalWrite(ledPin, LOW); // ESP8266 LED is active LOW
  server.send(200, "text/html", HTMLPage());
}

// Handle LED OFF request
void handleLEDOff() {
  ledState = false;
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/html", HTMLPage());
}

void setup() {
  Serial.begin(115200);
  
  // Initialize built-in LED pin as output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // Start with LED off
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.println(WiFi.localIP());
  
  // Define server routes
  server.on("/", handleRoot);
  server.on("/on", handleLEDOn);
  server.on("/off", handleLEDOff);
  
  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient(); // Handle client requests
}
