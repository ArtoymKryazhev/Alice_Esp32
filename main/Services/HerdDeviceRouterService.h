#include "libraries/ArduinoJson/src/ArduinoJson/Json/JsonSerializer.hpp"
#ifndef HERD_DEVICE_ROUTER_SERVICE_H
#define HERD_DEVICE_ROUTER_SERVICE_H

#include "Models/DeviceModel.h"
#include "Models/LedDeviceModel.h"
#include "Models/RelayDeviceModel.h"
#include "Services/LedDeviceService.h"
//#include "Services/RelayDeviceService.h"

class HerdDeviceRouterService {
public:
    // Метод для обработки устройства и его состояния
    static void processDevice(DeviceModel& device, const JsonArray& capabilities) {
        HardDeviceModel* hardDevice = device.getHardDevice();

        switch (device.getDeviceType()) {
            case DeviceTypeEnum::LIGHT: {
                LedDeviceModel* ledDevice = static_cast<LedDeviceModel*>(hardDevice);
                LedDeviceService::handle(ledDevice, capabilities);
                break;
            }
            // Добавь другие типы устройств по мере надобности
            default:
                Serial.println("Unknown device type");
                break;
        }
    }
};

#endif // HERD_DEVICE_ROUTER_SERVICE_H
