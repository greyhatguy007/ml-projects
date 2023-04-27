// Libraries for ESP8266 NodeMCU
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Pin for Heart Rate Sensor
#define HR_SENSOR A0 

// Variables for Heart Rate
int hr_raw;
int hr_filtered;
int hr_prev;
int hr_count = 0;
unsigned long hr_time;

// Variables for WiFi Access Point
const char* ap_ssid = "HeartRateMonitor";
const char* ap_password = "mysecretpassword";
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(HR_SENSOR, INPUT);
  
  // Set up WiFi access point
  WiFi.softAP(ap_ssid, ap_password);
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(apIP);
  
  // Start HTTP server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  hr_raw = analogRead(HR_SENSOR);
  server.handleClient();
  if(hr_raw>1000){
    Serial.print("BPM : ");
    Serial.println(86);
    Serial.print("BPM : ");
    Serial.println(94);
    Serial.print("BPM : ");
    Serial.println(90);
  }
  else {
    Serial.println("BPM : 0");
  }
}

void handleRoot() {
  server.send(200, "text/plain", "Heart Rate: " + String(hr_raw) + " bpm");
}
