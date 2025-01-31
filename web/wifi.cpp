#include <WiFi.h>
#include "wifi.h"

const char* ssid = "bwmax";
const char* password = "KabyLake101#";

void connectToWiFi() {
  Serial.println("Establishing connection to WiFi...");

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.print("Connected to WiFi with IP: ");
  Serial.println(WiFi.localIP());
}
