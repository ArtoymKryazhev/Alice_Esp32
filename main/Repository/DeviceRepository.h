#ifndef DEVICE_REPOSITORY_H
#define DEVICE_REPOSITORY_H

#include "Models/RelayDeviceModel.h"
#include "Models/LedDeviceModel.h"
#include "Models/DeviceModel.h"
#include <ArduinoJson.h>
#include <vector>
#include <optional>

class DeviceRepository {
private:
    static std::vector<DeviceModel> devices;  // Статический контейнер для устройств

    // Приватный метод для создания всех устройств (выполняется один раз)
    static void initializeDevices() {
        // Пример создания устройств
        std::vector<CapabilityModel> capabilities = {
            CapabilityModel(CapabilityTypeEnum::ON_OFF)
        };

        DeviceInfoModel deviceInfo("manufacturer", "model", "hw_version", "sw_version");

        // relay устройства 
        devices.push_back(DeviceModel(
            "relay-light-diod-1", "Реле Светодиод 1", new RelayDeviceModel("relay_1", 27, 25, 26, 0), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "relay-light-diod-2", "Реле Светодиод 2", new RelayDeviceModel("relay_1", 27, 25, 26, 1), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "relay-light-diod-3", "Реле Светодиод 3", new RelayDeviceModel("relay_1", 27, 25, 26, 2), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "relay-light-diod-4", "Реле Светодиод 4", new RelayDeviceModel("relay_1", 27, 25, 26, 3), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "relay-light-diod-5", "Реле Светодиод 5", new RelayDeviceModel("relay_1", 27, 25, 26, 4), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "relay-light-diod-6", "Реле Светодиод 6", new RelayDeviceModel("relay_1", 27, 25, 26, 5), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "relay-light-diod-7", "Реле Светодиод 7", new RelayDeviceModel("relay_1", 27, 25, 26, 6), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "relay-light-diod-8", "Реле Светодиод 8", new RelayDeviceModel("relay_1", 27, 25, 26, 7), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));


        // led устройства 

        devices.push_back(DeviceModel(
            "light-diod-1", "Светодиод 1", new LedDeviceModel("led_1", 5), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));
    }

public:
    // Получение всех устройств
    static std::vector<DeviceModel>& getAllDevice() {
        if (devices.empty()) {  // Если устройства ещё не созданы, создаём их
            initializeDevices();
        }
        return devices;
    }

    // Получение устройства по ID
    static std::optional<DeviceModel> getDeviceById(const std::string& id) {
        if (devices.empty()) {  // Если устройства ещё не созданы, создаём их
            initializeDevices();
        }
        for (auto& device : devices) {
            if (device.getId() == id) {
                return device;
            }
        }
        return std::nullopt;
    }
};

// Инициализация статического контейнера
std::vector<DeviceModel> DeviceRepository::devices;

#endif // DEVICE_REPOSITORY_H
