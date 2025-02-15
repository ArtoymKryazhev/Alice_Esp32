#ifndef DEVICE_REPOSITORY_H
#define DEVICE_REPOSITORY_H

#include "Models/RelayDeviceModel.h"
#include "Models/DeviceModel.h"
#include <ArduinoJson.h>
#include <vector>
#include <optional>

class DeviceRepository {
public:
    // Получение всех устройств
   static std::vector<DeviceModel> getAllDevice() {
        std::vector<DeviceModel> devices;
        
        // Пример создания устройств
        std::vector<CapabilityModel> capabilities = {
            CapabilityModel(CapabilityTypeEnum::ON_OFF)
        };

        DeviceInfoModel deviceInfo("manufacturer", "model", "hw_version", "sw_version");

        devices.push_back(DeviceModel(
            "light-diod-1", "Светодиод 1", RelayDeviceModel("relay_1", 27, 25, 26, 0), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-2", "Светодиод 2", RelayDeviceModel("relay_1", 27, 25, 26, 1), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-3", "Светодиод 3", RelayDeviceModel("relay_1", 27, 25, 26, 2), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-4", "Светодиод 4", RelayDeviceModel("relay_1", 27, 25, 26, 3), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-5", "Светодиод 5", RelayDeviceModel("relay_1", 27, 25, 26, 4), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-6", "Светодиод 6", RelayDeviceModel("relay_1", 27, 25, 26, 5), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-7", "Светодиод 7", RelayDeviceModel("relay_1", 27, 25, 26, 6), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-8", "Светодиод 8", RelayDeviceModel("relay_1", 27, 25, 26, 7), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        return devices;
    }

    // Получение устройства по ID
    static std::optional<DeviceModel> getDeviceById(const std::string& id) {
        std::vector<DeviceModel> devices = getAllDevice();  // Получаем все устройства
        for (auto& device : devices) {
            if (device.getId() == id) {
                return device;
            }
        }
        return std::nullopt;
    }
};

#endif // DEVICE_REPOSITORY_H
