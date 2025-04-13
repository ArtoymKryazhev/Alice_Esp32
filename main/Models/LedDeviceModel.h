#ifndef LED_DEVICE_MODEL_H
#define LED_DEVICE_MODEL_H

#include <Arduino.h>
#include "HardDeviceModel.h"
#include "PinModel/PinOnOffModel.h"

class LedDeviceModel : public HardDeviceModel {
private:
    String id;       // Уникальный ID устройства
    PinOnOffModel pin;  // Пин для подачи питания

public:
    // Конструктор
    LedDeviceModel(const String& id, PinOnOffModel pin)
        : id(id), pin(pin) {}

    const String& getId() const { return id; }

    // Геттер для получения номера пина
    int getPinNumber() const { return pin.getPinNumber(); }

    // Сеттер для изменения номера пина
    void setPinNumber(int newPinNumber) { pin.setPinNumber(newPinNumber); }
    
    // Метод включения LED
    void turnOn() {
        pin.turnOn(); // Включаем пин
    }

    // Метод выключения LED
    void turnOff() {
        pin.turnOff(); // Выключаем пин
    }
};

#endif // LED_DEVICE_MODEL_H
