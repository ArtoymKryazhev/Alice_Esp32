#ifndef PIN_SERVICE_H
#define PIN_SERVICE_H

#include <Arduino.h>
#include "Repository/DeviceRepository.h"
#include "Models/PinModel/BasePinModel.h"
#include "Enums/PinTypeEnum.h"
#include <vector>

class PinService {
public:
    // Устанавливает режим пина, если он задан в PinModel
    static void setPinMode(const BasePinModel& pin) {
        pinMode(pin.getPinNumber(), getArduinoPinMode(pin.getPinMode()));
    }

    // Устанавливает состояние пина
    static void setPinState(const BasePinModel& pin, PinStateEnum state) {
        digitalWrite(pin.getPinNumber(), getArduinoPinState(state));
    }

    // Инициализация всех пинов при старте платы
    static void initializeAllPins() {
        // Получаем все устройства
        std::vector<DeviceModel>& devices = DeviceRepository::getAllDevice();

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
