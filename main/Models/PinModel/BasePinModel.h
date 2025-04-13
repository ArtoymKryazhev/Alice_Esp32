#ifndef BASE_PIN_MODEL_H
#define BASE_PIN_MODEL_H

#include "Enums/PinTypeEnums.h"

class BasePinModel {
protected:
    int pinNumber;
    PinModeEnum mode;

public:
    // Конструктор
    BasePinModel(int pin, PinModeEnum pinMode) 
        : pinNumber(pin), mode(pinMode) {}

    // Виртуальный деструктор (обеспечивает корректное удаление потомков)
    virtual ~BasePinModel() = default;

    // Геттер
    int getPinNumber() const { return pinNumber; }

    // Сеттер (опционально, можно убрать, если не нужен)
    void setPinNumber(int number) { pinNumber = number; }

    // Геттер для получения режима пина
    PinModeEnum getPinMode() const { return mode; }     

    // Сеттер для изменения режима пина
    void setPinMode(PinModeEnum newMode) { mode = newMode; }
        
};

#endif // BASE_PIN_MODEL_H
