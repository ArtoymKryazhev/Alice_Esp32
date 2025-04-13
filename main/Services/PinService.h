#ifndef PIN_SERVICE_H
#define PIN_SERVICE_H

#include <Arduino.h>
#include "Models/PinModel.h"
#include "Enums/PinTypeEnums.h"

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
};

#endif // PIN_SERVICE_H
