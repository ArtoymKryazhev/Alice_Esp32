#ifndef CONNECT_TO_WIFI_H
#define CONNECT_TO_WIFI_H

#include <WiFi.h>

// Функция подключения к Wi-Fi
void connectToWiFi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password); // Инициализация подключения
  Serial.println("Establishing connection to WiFi with SSID: " + String(ssid));

  // Ожидание подключения
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".-");
  }
  
  // Подключение успешно
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

#endif // CONNECT_TO_WIFI_H
