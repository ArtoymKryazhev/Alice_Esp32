#ifndef PINMODEL_H
#define PINMODEL_H

#include "DeviceModel.h"  // Подключаем модель устройства (DeviceRepository)
#include "Enums/PinTypeEnum.h"  // Подключаем enum типы пинов
#include <optional>

class PinModel {
private:
    int pinNumber;  // Номер пина
    DeviceModel* device;  // Устройство, к которому привязан пин

    std::optional<PinModeEnum> modeEnum;                  // Режим пина
    std::optional<PinStateEnum> stateEnum;                // Текущее состояние пина
    std::optional<CommunicationProtocolEnum> protocolEnum; // Протокол связи
    std::optional<BootModeEnum> bootModeEnum;             // Режим загрузки
    std::optional<SpecialFunctionEnum> specialFunctionEnum; // Специальная функция пина
    std::optional<StrappingPinsEnum> strappingPinsEnum;   // Страппинг пины

public:
    // Конструктор с обязательными параметрами и необязательными с дефолтными значениями
    PinModel(int pinNumber, DeviceModel* device,
             std::optional<PinModeEnum> modeEnum = std::nullopt,
             std::optional<PinStateEnum> stateEnum = std::nullopt,
             std::optional<CommunicationProtocolEnum> protocolEnum = std::nullopt,
             std::optional<BootModeEnum> bootModeEnum = std::nullopt,
             std::optional<SpecialFunctionEnum> specialFunctionEnum = std::nullopt,
             std::optional<StrappingPinsEnum> strappingPinsEnum = std::nullopt)
        : pinNumber(pinNumber),
          device(device),
          modeEnum(modeEnum),
          stateEnum(stateEnum),
          protocolEnum(protocolEnum),
          bootModeEnum(bootModeEnum),
          specialFunctionEnum(specialFunctionEnum),
          strappingPinsEnum(strappingPinsEnum) {}

    // Геттеры и сеттеры
    int getPinNumber() const { return pinNumber; }
    void setPinNumber(int number) { pinNumber = number; }

    DeviceModel* getDevice() const { return device; }
    void setDevice(DeviceModel* dev) { device = dev; }

    std::optional<PinModeEnum> getModeEnum() const { return modeEnum; }
    void setModeEnum(std::optional<PinModeEnum> m) { modeEnum = m; }

    std::optional<PinStateEnum> getStateEnum() const { return stateEnum; }
    void setStateEnum(std::optional<PinStateEnum> s) { stateEnum = s; }

    std::optional<CommunicationProtocolEnum> getProtocolEnum() const { return protocolEnum; }
    void setProtocolEnum(std::optional<CommunicationProtocolEnum> p) { protocolEnum = p; }

    std::optional<BootModeEnum> getBootModeEnum() const { return bootModeEnum; }
    void setBootModeEnum(std::optional<BootModeEnum> b) { bootModeEnum = b; }

    std::optional<SpecialFunctionEnum> getSpecialFunctionEnum() const { return specialFunctionEnum; }
    void setSpecialFunctionEnum(std::optional<SpecialFunctionEnum> sf) { specialFunctionEnum = sf; }

    std::optional<StrappingPinsEnum> getStrappingPinsEnum() const { return strappingPinsEnum; }
    void setStrappingPinsEnum(std::optional<StrappingPinsEnum> sp) { strappingPinsEnum = sp; }

    // Методы для работы с пином (заглушки)
    void getPinState();   // Заглушка для получения состояния пина
    void setPinState(PinStateEnum state); // Заглушка для установки состояния пина
    bool isPinCompatibleWithAction(); // Проверка совместимости пина с операцией (заглушка)
};

#endif // PINMODEL_H
