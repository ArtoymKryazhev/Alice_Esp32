#ifndef DEVICE_INFO_MODEL_H
#define DEVICE_INFO_MODEL_H

#include <ArduinoJson.h>
#include <optional>

class DeviceInfoModel {
private:
    String manufacturer;
    String model;
    std::optional<String> hw_version;
    std::optional<String> sw_version;

public:
    // Конструктор с обязательными параметрами и необязательными с дефолтными значениями
    DeviceInfoModel(const String& manufacturer, const String& model, 
                    std::optional<String> hw_version = std::nullopt, 
                    std::optional<String> sw_version = std::nullopt)
        : manufacturer(manufacturer), model(model) 
    {
        // Если hw_version не передан, используем значение по умолчанию
        if (!hw_version.has_value()) {
            this->hw_version = "1.0"; // Значение по умолчанию для hw_version
        } else {
            this->hw_version = hw_version;
        }

        // Если sw_version не передан, используем значение по умолчанию
        if (!sw_version.has_value()) {
            this->sw_version = "1.0"; // Значение по умолчанию для sw_version
        } else {
            this->sw_version = sw_version;
        }
    }

    // Метод для сериализации в JSON
    void serializeToJson(JsonDocument& doc) const {
        doc["manufacturer"] = manufacturer;
        doc["model"] = model;

        if (hw_version.has_value()) {
            doc["hw_version"] = hw_version.value();
        }
        if (sw_version.has_value()) {
            doc["sw_version"] = sw_version.value();
        }
    }
};

#endif // DEVICE_INFO_MODEL_H
