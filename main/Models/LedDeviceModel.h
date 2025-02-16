#ifndef LED_DEVICE_MODEL_H
#define LED_DEVICE_MODEL_H

#include <Arduino.h>
#include "HardDeviceModel.h"
#include "PinModel.h"

class LedDeviceModel : public HardDeviceModel {
private:
    String id;       // Уникальный ID устройства
    PinModel powerPin;  // Пин для подачи питания

public:
    // Конструктор
    LedDeviceModel(const String& id, PinModel powerPin)
        : id(id), powerPin(powerPin) {}

    // Геттеры
    const String& getId() const { return id; }
    const PinModel& getPowerPin() const { return powerPin; }
};

#endif // LED_DEVICE_MODEL_H
