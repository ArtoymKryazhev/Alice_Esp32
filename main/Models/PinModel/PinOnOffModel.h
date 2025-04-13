#ifndef PIN_ON_OFF_MODEL_H
#define PIN_ON_OFF_MODEL_H

#include "BasePinModel.h"
#include "Interface/PinOnOffInterface.h"
#include "Services/PinService.h"
#include "Enums/PinTypeEnum.h"

class PinOnOffModel : public BasePinModel, public PinOnOffInterface {
public:
    // Конструктор: передаём номер пина и режим
    explicit PinOnOffModel(int pinNumber, PinModeEnum pinMode)
        : BasePinModel(pinNumber, pinMode) {}

    // Реализация методов интерфейса
    void turnOn() override {
        PinService::setPinState(*this, PinStateEnum::DIGITAL_HIGH);
    }

    void turnOff() override {
        PinService::setPinState(*this, PinStateEnum::DIGITAL_LOW);
    }
};

#endif // PIN_ON_OFF_MODEL_H
