#include "libraries/ArduinoJson/src/ArduinoJson/Json/JsonSerializer.hpp"
#ifndef HERD_DEVICE_ROUTER_SERVICE_H
#define HERD_DEVICE_ROUTER_SERVICE_H

#include "Models/DeviceModel.h"
#include "Models/LedDeviceModel.h"
#include "Models/RelayDeviceModel.h"
#include "Models/ActionResultModel.h"
#include "Models/StateModel"
#include "Enums/CapabilityTypeEnum"
#include "Services/LedDeviceService.h"
//#include "Services/RelayDeviceService.h"
#include <ArduinoJson.h>
#include <vector>
#include <optional>

class HerdDeviceRouterService {
public:
    // Метод для обработки устройства и его состояния
    static ActionResultModel processDevice(DeviceModel& device, const JsonArray& capabilities) {
        HardDeviceModel* hardDevice = device.getHardDevice();

        switch (device.getDeviceType()) {
        case DeviceTypeEnum::LIGHT: {
            LedDeviceModel* ledDevice = static_cast<LedDeviceModel*>(hardDevice);
            return LedDeviceService::handle(ledDevice, capabilities);
        }
        // Добавь другие типы устройств по мере надобности
        default:

            return ActionResultModel(
                ActionResultStatusEnum::ERROR,
                ErrorCodeEnum::INVALID_ACTION,
                "Неизвестный тип устройства"
            );
        }
    }

    static StateModel stateDevice(DeviceModel& device, const CapabilityTypeEnum type) {
        HardDeviceModel* hardDevice = device.getHardDevice();

        switch (device.getDeviceType()) {
        case DeviceTypeEnum::LIGHT: {
            LedDeviceModel* ledDevice = static_cast<LedDeviceModel*>(hardDevice);
            return LedDeviceService::stateDevice(ledDevice, type);
        }
        // Добавь другие типы устройств по мере надобности
        default:

            return ActionResultModel(
                ActionResultStatusEnum::ERROR,
                ErrorCodeEnum::INVALID_ACTION,
                "Неизвестный тип устройства"
            );
        }
    }
};

#endif // HERD_DEVICE_ROUTER_SERVICE_H
