#include "esp32-hal-gpio.h"
#ifndef PIN_SERVICE_H
#define PIN_SERVICE_H

#include "Repository/DeviceRepository.h"
#include <Arduino.h>
#include "Models/DeviceModel.h"
#include "Models/PinModel/BasePinModel.h"
#include "Enums/PinTypeEnum.h"
#include <vector>

class PinService {
public:
    // Устанавливает режим пина, если он задан в PinModel
    static void setPinMode(const BasePinModel& pin) {
        if (pin.getPinMode() == PinModeEnum::DIGITAL_OUTPUT) {
            pinMode(pin.getPinNumber(), OUTPUT);
        }
        else if (pin.getPinMode() == PinModeEnum::DIGITAL_INPUT) {
            pinMode(pin.getPinNumber(), INPUT);
        } else {
            Serial.println("Такого мода не существует.");
        }
    }

    // Устанавливает состояние пина
    static void setPinState(const BasePinModel& pin, PinStateEnum state) {
        digitalWrite(pin.getPinNumber(), getArduinoPinState(state));
    }

    // Инициализация всех пинов при старте платы
    static void initializeAllPins(std::vector<DeviceModel>& devices) {
        // Проходим по каждому устройству
        for (DeviceModel& device : devices) {
            // Получаем хардварную часть устройства
            HardDeviceModel* hardDevice = device.getHardDevice();
            // Получаем список всех пинов устройства и инициализируем каждый
            for (const BasePinModel* pin : hardDevice->getAllPin()) {
                setPinMode(*pin);
            }
        }
    }
};

#endif // PIN_SERVICE_H
