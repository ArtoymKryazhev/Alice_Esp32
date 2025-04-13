#ifndef RELAY_DEVICE_MODEL_H
#define RELAY_DEVICE_MODEL_H

#include <Arduino.h>
#include "HardDeviceModel.h"
#include "PinModel/PinOnOffModel.h"
#include "Enums/PinTypeEnum.h"


class RelayDeviceModel : public HardDeviceModel{
private:
    String id;       // Уникальный ID реле
    PinOnOffModel serPin;      // Пин SER (вход данных)
    PinOnOffModel rclkPin;     // Пин RCLK (сдвиг регистра)
    PinOnOffModel srclkPin;    // Пин SRCLK (сдвиг такта)
    int relayIndex;  
    static constexpr int totalRelays = 16; 

public:
    // Конструктор
    RelayDeviceModel(const String& id, PinOnOffModel serPin, PinOnOffModel rclkPin, PinOnOffModel srclkPin, int relayIndex)
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

    //реализация 
};

#endif // RELAY_DEVICE_MODEL_H
