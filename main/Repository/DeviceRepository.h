#ifndef DEVICE_REPOSITORY_H
#define DEVICE_REPOSITORY_H

#include "Models/DeviceModel.h"
#include <vector>
#include <optional>

class DeviceRepository {
public:
    // Получение всех устройств
    static std::vector<DeviceModel> getAllDevices() {
        std::vector<DeviceModel> devices;

        // Пример создания устройств
        std::vector<CapabilityModel> capabilities = {
            CapabilityModel(CapabilityTypeEnum::ON_OFF)
        };

        DeviceInfoModel deviceInfo("manufacturer", "model", "hw_version", "sw_version");

        devices.push_back(DeviceModel(
            "light-diod-1", "Светодиод 1", DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-2", "Светодиод 2", DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        return devices;
    }

    // Получение устройства по ID
    static std::optional<DeviceModel> getDeviceById(const std::string& id) {
        std::vector<DeviceModel> devices = getAllDevices();  // Получаем все устройства
        for (auto& device : devices) {
            if (device.getId() == id) {
                return device;
            }
        }
        return std::nullopt;
    }
};

#endif // DEVICE_REPOSITORY_H
