#ifndef PINMODEL_H
#define PINMODEL_H

#include "Enums/PinTypeEnum.h"  // Подключаем enum типы пинов
#include <optional>

class PinModel {
private:
    int pinNumber;  // Номер пина
    std::optional<PinModeEnum> mode;                // Текущее состояние пина

public:
    // Конструктор с обязательными параметрами и необязательными с дефолтными значениями
    PinModel(int pinNumber, std::optional<PinModeEnum> mode = std::nullopt)
    : pinNumber(pinNumber), mode(mode) {}

    // Геттеры и сеттеры
    int getPinNumber() const { return pinNumber; }
    void setPinNumber(int number) { pinNumber = number; }

    std::optional<PinModeEnum> getPinMode() const { return mode; }
    void setModeEnum(std::optional<PinModeEnum> m) { mode = m; }


        // Методы для работы с пином (заглушки)
    void getPinState();   // Заглушка для получения состояния пина
    void setPinState(PinStateEnum state); // Заглушка для установки состояния пина
    bool isPinCompatibleWithAction(); // Проверка совместимости пина с операцией (заглушка)
};

#endif // PINMODEL_H
