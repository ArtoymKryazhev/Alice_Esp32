#ifndef DEVICE_MODEL_H
#define DEVICE_MODEL_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>
#include <optional>
#include <string>
#include "C:/Dev/Edu/Arduino/Alice_Esp32/main/Enums/CapabilityTypeEnum.h"
#include "C:/Dev/Edu/Arduino/Alice_Esp32/main/Enums/DeviceTypeEnum.h"
#include "DeviceInfoModel.h"
#include "CapabilityModel.h"

class DeviceModel {

private:
    std::string id;
    std::string name;
    std::vector<CapabilityModel> capabilities;
    DeviceTypeEnum type;
    std::optional<DeviceInfoModel> deviceInfo;
    std::optional<std::string> description; // Сделаем описание опциональным

public:
    // Конструктор с обязательными параметрами и необязательными с дефолтными значениями
    DeviceModel(const std::string& id, const std::string& name, DeviceTypeEnum type,
                const std::vector<CapabilityModel>& capabilities, 
                std::optional<DeviceInfoModel> deviceInfo = std::nullopt, 
                std::optional<std::string> description = std::nullopt)
        : id(id), name(name), capabilities(capabilities), type(type), deviceInfo(deviceInfo), description(description) {}

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

        // Добавляем описание, если оно существует
        if (description.has_value()) {
            doc["description"] = description.value();
        }

        // Сериализация deviceInfo, если оно существует
        if (deviceInfo) {
            JsonDocument deviceInfoDoc;  // Создаем временный документ для сериализации deviceInfo
            deviceInfo->serializeToJson(deviceInfoDoc);  // Сериализуем deviceInfo в deviceInfoDoc
            doc["device_info"] = deviceInfoDoc.as<JsonObject>();
        }
    }

    const std::string& getId() const {return id;}
};

#endif // DEVICE_MODEL_H
