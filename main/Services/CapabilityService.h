#ifndef CAPABILITY_SERVICE_H
#define CAPABILITY_SERVICE_H

#include "Models/CapabilityModel.h"  // Модель, с которой будет работать сервис
#include "Models/ActionResultModel.h"  // Результат действия
#include "Enums/CapabilityTypeEnum.h"
#include "Models/StateModel.h"
#include <ArduinoJson.h>

// Сервис, работающий с моделями Capability
class CapabilityService {
public:
    // Метод для установки состояния и результата действия в модель
    static void setActionStatus(CapabilityModel& capability, const String& instance, const ActionResultModel& actionResult) {
        // Если состояние отсутствует, создаем его
        if (!capability.hasState()) {
            capability.setState(StateModel(instance, std::nullopt, std::nullopt));  // Используем корректный конструктор
        }
        capability.setActionStatus(actionResult);  // Обновляем результат действия в состоянии
    }

    // Метод для проверки, есть ли состояние в модели
    static bool hasState(const CapabilityModel& capability) {
        return capability.getState().has_value();  // Проверяем, есть ли состояние
    }

    // Статический метод для создания объекта CapabilityModel из JsonObject
    static CapabilityModel from(const JsonObject& data) {
        CapabilityTypeEnum type = CapabilityTypeEnum::UNKNOWN;  // Тип по умолчанию (неизвестный)
        std::optional<StateModel> state = std::nullopt;  // Состояние по умолчанию

        // Создаём модель типа CapabilityTypeEnum из данных JSON
        if (!data["type"].isNull()) {
            type = fromCapabilityTypeEnum(data);  // Преобразуем строку в тип CapabilityTypeEnum
        }

        // Проверяем наличие состояния и если оно есть, создаём объект StateModel
        if (!data["state"].isNull()) {
            state = StateModel::from(data["state"]);  // Загружаем состояние из JSON
        }

        // Возвращаем объект CapabilityModel с типом и состоянием
        return CapabilityModel(type, state);
    }

    // Статический метод для создания объектов из массива и сохранения в JsonArray
    static JsonArray fromBatch(const JsonArray& capabilities, JsonArray& JsonArrayCapabilities) {
        for (JsonObject capability : capabilities) {
            // Пробуем создать CapabilityModel
            if (fromCapabilityTypeEnum(capability) != CapabilityTypeEnum::UNKNOWN) {
                // Создаём объект CapabilityModel
                CapabilityModel capabilityModelOpt = CapabilityService::from(capability);
                JsonDocument doc;
                capabilityModelOpt.serializeToJson(doc);  // Сериализуем объект в JSON
                JsonArrayCapabilities.add(doc);  // Добавляем сериализованный объект в массив
            } else {
                Serial.println("Skipping invalid capability.");  // Пропускаем недействительные возможности
                continue;
            }
        }

        return JsonArrayCapabilities;  // Возвращаем массив с сериализованными объектами
    }
};

#endif // CAPABILITY_SERVICE_H
