#ifndef DEVICE_REPOSITORY_H
#define DEVICE_REPOSITORY_H

#include "Models/RelayDeviceModel.h"
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

        // Создаём устройства, используя std::make_unique для управления памятью
        devices.push_back(DeviceModel(
            "light-diod-1", "Светодиод 1", new RelayDeviceModel("relay_1", 27, 25, 26, 0), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-2", "Светодиод 2", new RelayDeviceModel("relay_1", 27, 25, 26, 1), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-3", "Светодиод 3", new RelayDeviceModel("relay_1", 27, 25, 26, 2), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-4", "Светодиод 4", new RelayDeviceModel("relay_1", 27, 25, 26, 3), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-5", "Светодиод 5", new RelayDeviceModel("relay_1", 27, 25, 26, 4), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-6", "Светодиод 6", new RelayDeviceModel("relay_1", 27, 25, 26, 5), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-7", "Светодиод 7", new RelayDeviceModel("relay_1", 27, 25, 26, 6), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
        ));

        devices.push_back(DeviceModel(
            "light-diod-8", "Светодиод 8", new RelayDeviceModel("relay_1", 27, 25, 26, 7), DeviceTypeEnum::LIGHT, capabilities, deviceInfo
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
