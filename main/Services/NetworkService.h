#ifndef NETWORK_SERVICE_H
#define NETWORK_SERVICE_H

#include <Arduino.h>
#include <WiFi.h>

/**
 * @brief Сервис для управления подключением к Wi-Fi.
 */
class NetworkService {
public:
    /**
     * @brief Подключается к Wi-Fi с заданными параметрами.
     * @param ssid Имя Wi-Fi сети.
     * @param password Пароль от Wi-Fi.
     */
    static void connect(const char* ssid, const char* password) {
        WiFi.begin(ssid, password);
        Serial.print("Подключение к Wi-Fi");
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.print(".");
        }
        Serial.println();
        Serial.print("Подключено. IP-адрес: ");
        Serial.println(WiFi.localIP());
    }
};

#endif // NETWORK_SERVICE_H
