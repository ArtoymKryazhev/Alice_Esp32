#include "HardwareSerial.h"
#ifndef LED_DEVICE_SERVICE_H
#define LED_DEVICE_SERVICE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Models/LedDeviceModel.h"
#include "Services/PinService.h"

class LedDeviceService {
public:
    static void handle(LedDeviceModel* ledDevice, const JsonArray& capabilities) {
        for (JsonObject capability : capabilities) {
            const char* type = capability["type"];
            
            // Проверка типа способности
            if (strcmp(type, "devices.capabilities.on_off") == 0) {
                bool value = capability["state"]["value"];
                
                if (value){
                  ledDevice->turnOn();
                } else {
                  ledDevice->turnOff();
                }
            }
        }
    }
};

#endif // LED_DEVICE_SERVICE_H
