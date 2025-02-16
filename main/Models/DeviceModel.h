#ifndef DEVICE_MODEL_H
#define DEVICE_MODEL_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>
#include <optional>
#include <string>


#include "Enums/CapabilityTypeEnum.h"   
#include "Enums/DeviceTypeEnum.h"

#include "DeviceInfoModel.h"
#include "CapabilityModel.h"
#include "HardDeviceModel.h"

class DeviceModel {

private:
    std::string id;
    std::string name;
    HardDeviceModel* hardDevice;
    std::vector<CapabilityModel> capabilities;
    DeviceTypeEnum type;
    std::optional<DeviceInfoModel> deviceInfo;
    
public:
    // Конструктор с обязательными параметрами и необязательными с дефолтными значениями
    DeviceModel(const std::string& id, const std::string& name, HardDeviceModel* hardDevice,
                DeviceTypeEnum type, const std::vector<CapabilityModel>& capabilities, 
                std::optional<DeviceInfoModel> deviceInfo = std::nullopt)
        : id(id), name(name), hardDevice(hardDevice), capabilities(capabilities), type(type), deviceInfo(deviceInfo) {}

    // Получить Capability по типу

    CapabilityModel* getCapabilityByType(const String type) {
        for (auto& capability : capabilities) {
            if (capabilityTypeToString(capability.getType()) == type) {
                return &capability;
            }
        }
        return nullptr;
    }

    // Сериализация в JSON
    void serializeToJson(JsonDocument& doc) const {
        doc["id"] = id;
        doc["name"] = name;
        doc["type"] = deviceTypeToString(type);

        JsonArray capabilitiesArray = doc["capabilities"].to<JsonArray>();

        // Перебираем все элементы вектора capabilities
        for (const auto& capability : capabilities) {
            JsonDocument capabilityJson;  // создаём объект для каждого элемента
            capability.serializeToJson(capabilityJson);  // сериализуем объект
            capabilitiesArray.add(capabilityJson);  // добавляем объект в массив
        }

        // Сериализация deviceInfo, если оно существует
        if (deviceInfo) {
            JsonDocument deviceInfoDoc;  // Создаем временный документ для сериализации deviceInfo
            deviceInfo->serializeToJson(deviceInfoDoc);  // Сериализуем deviceInfo в deviceInfoDoc
            doc["device_info"] = deviceInfoDoc.as<JsonObject>();
        }
    }

    const std::string& getId() const {return id;}
    HardDeviceModel* getHardDevice() const {return hardDevice;}
};

#endif // DEVICE_MODEL_H
