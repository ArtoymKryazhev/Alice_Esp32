#ifndef RESPONSE_MODEL_H
#define RESPONSE_MODEL_H

#include <ArduinoJson.h>
#include <vector>
#include "Utils/UUID.h"  // Используем класс для генерации UUID
#include "Models/DeviceModel.h"  // Подключаем модель устройства

class ResponseModel {
private:
    std::vector<DeviceModel> devices;  // Список устройств

public:
    // Конструктор, принимающий список устройств
    ResponseModel(const std::vector<DeviceModel>& devices)
        : devices(devices) {}

    // Метод для сериализации объекта в JSON
    void serializeToJson(JsonDocument& doc) const {
        // Генерация уникального идентификатора для запроса
        String requestId = UUID::generate();

        // Заполнение JSON-объекта
        doc["request_id"] = requestId;  // Идентификатор запроса

        // Создание объекта payload для вложенных данных
        JsonObject payload = doc["payload"].to<JsonObject>();
        payload["user_id"] = "Some-user-id";  // Пример user_id

        // Добавление устройств в массив devices
        JsonArray devicesArray = payload["devices"].to<JsonArray>();
        
        // Сериализация каждого устройства и добавление в массив
        for (const auto& device : devices) {
            JsonDocument deviceJson;
            device.serializeToJson(deviceJson);  // Сериализация устройства
            devicesArray.add(deviceJson);  // Добавление устройства в массив
        }
    }
};

#endif  // RESPONSE_MODEL_H
