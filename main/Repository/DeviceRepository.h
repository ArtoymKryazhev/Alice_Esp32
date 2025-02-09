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

        devices.push_back(DeviceModel(
            "light-diod-3", "Светодиод 3", DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-4", "Светодиод 4", DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-5", "Светодиод 5", DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-6", "Светодиод 6", DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-7", "Светодиод 7", DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-8", "Светодиод 8", DeviceTypeEnum::LIGHT, capabilities, deviceInfo
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
