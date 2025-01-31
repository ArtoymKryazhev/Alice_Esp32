#ifndef RESPONSE_MODEL_H
#define RESPONSE_MODEL_H

#include <ArduinoJson.h>
#include <vector>
#include "C:/Dev/Edu/Arduino/Alice_Esp32/main/Utils/UUID.h"  // Используем ваш класс для генерации UUID
#include "C:/Dev/Edu/Arduino/Alice_Esp32/main/Models/DeviceModel.h"  // Подключение DeviceModel

class ResponseModel {
private:
    std::vector<DeviceModel> devices;  // Список устройств

public:
    // Конструктор
    ResponseModel(const std::vector<DeviceModel>& devices)
        : devices(devices) {}

    // Метод для сериализации в JSON
    void serializeToJson(JsonDocument& doc) const {
        // Генерация request_id
        String requestId = UUID::generate();

        // Заполнение JSON-объекта
        doc["request_id"] = requestId;

        // Создание объекта payload
        JsonObject payload = doc["payload"].to<JsonObject>();
        payload["user_id"] = "Some-user-id";

        // Добавление устройств в payload
        JsonArray devicesArray = payload["devices"].to<JsonArray>();
        
        for (const auto& device : devices) {
            JsonDocument deviceJson;
            device.serializeToJson(deviceJson);
            devicesArray.add(deviceJson);
        }
    }
};

#endif  // RESPONSE_MODEL_H
