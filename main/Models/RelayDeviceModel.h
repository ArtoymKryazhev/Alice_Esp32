#ifndef RELAY_DEVICE_MODEL_H
#define RELAY_DEVICE_MODEL_H

#include <Arduino.h>
#include "HardDeviceModel.h"
#include "PinModel.h"
#include "Enums/PinTypeEnum.h"


class RelayDeviceModel : public HardDeviceModel{
private:
    String id;       // Уникальный ID реле
    PinModel serPin;      // Пин SER (вход данных)
    PinModel rclkPin;     // Пин RCLK (сдвиг регистра)
    PinModel srclkPin;    // Пин SRCLK (сдвиг такта)
    int relayIndex;  
    static constexpr int totalRelays = 16; 

public:
    // Конструктор
    RelayDeviceModel(const String& id, PinModel serPin, PinModel rclkPin, int srclkPin, int relayIndex)
        : id(id), serPin(serPin), rclkPin(rclkPin), srclkPin(srclkPin) {
        if (relayIndex < 0 || relayIndex >= totalRelays) {
            relayIndex = 0; // Если индекс неверный, ставим в 0 по умолчанию
        }
        this->relayIndex = relayIndex;
    }

    // Геттеры
    const String& getId() const { return id; }
    int getRelayIndex() const { return relayIndex; }
    int getTotalRelays() const { return totalRelays; } // Вернёт 16
};

#endif // RELAY_DEVICE_MODEL_H
