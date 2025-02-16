#include "libraries/ArduinoJson/src/ArduinoJson/Json/JsonSerializer.hpp"
#include "libraries/ArduinoJson/src/ArduinoJson/Document/JsonDocument.hpp"
#ifndef HERD_DEVICE_ROUTER_SERVICE_H
#define HERD_DEVICE_ROUTER_SERVICE_H

#include "Models/DeviceModel.h"
//#include "Services/RelayDeviceService.h"

class HerdDeviceRouterService {
public:
    // Метод для обработки устройства и его состояния
    static void processDevice(DeviceModel& device, const JsonArray& capabilities) {
        // Получаем физическое устройство
        HardDeviceModel* hardDevice = device.getHardDevice();

        // Определяем тип устройства
        if (RelayDeviceModel* relayDevice = static_cast<RelayDeviceModel*>(hardDevice)) {
            //RelayDeviceService::processRelayDevice(*relayDevice, state);
            
        }
        // Можно добавить другие типы устройств по аналогии
    }
};

#endif // HERD_DEVICE_ROUTER_SERVICE_H
