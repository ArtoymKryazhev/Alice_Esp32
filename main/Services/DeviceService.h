#ifndef DEVICE_SERVICE_H
#define DEVICE_SERVICE_H

#include "DeviceRepository.h" // Репозиторий с методами получения устройства
#include "DeviceModel.h"

class DeviceService {
public:
    // Метод для получения Capability по типу
    static CapabilityModel* getCapabilityByType(const std::string& deviceId, const std::string& type) {
        // Получаем устройство из репозитория
        auto device = DeviceRepository::getDeviceById(deviceId);
        if (device) {
            // Перебираем capabilities устройства
            for (auto& capability : device->capabilities) {
                if (capabilityTypeToString(capability.getType()) == type) {
                    return &capability; // Возвращаем найденную Capability
                }
            }
        }
        return nullptr; // Если не нашли, возвращаем nullptr
    }
};

#endif // DEVICE_SERVICE_H
