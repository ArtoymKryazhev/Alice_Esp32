#ifndef PIN_SERVICE_H
#define PIN_SERVICE_H

#include <Arduino.h>
#include "Models/PinModel.h"
#include "Enums/PinEnums.h"

class PinService {
public:
    // Устанавливает режим пина, если он задан в PinModel
    static void setPinMode(const PinModel& pin) {
        if (pin.getPinMode().has_value()) {  // Проверяем, задан ли режим
            pinMode(pin.getPinNumber(), getArduinoPinMode(pin.getMode().value()));
        }
    }

    // Устанавливает состояние пина
    static void setPinState(const PinModel& pin, PinStateEnum state) {
        digitalWrite(pin.getPin(), getArduinoPinState(state));
    }
};

#endif // PIN_SERVICE_H
