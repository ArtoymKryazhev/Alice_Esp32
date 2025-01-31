#ifndef CAPABILITYMODEL_H
#define CAPABILITYMODEL_H

#include <ArduinoJson.h>
#include <optional>
#include "Enums/CapabilityTypeEnum.h"
#include "StateModel.h"

// Модель, представляющая Capability (возможности устройства)
class CapabilityModel {
private:
    CapabilityTypeEnum type;                // Тип Capability
    std::optional<StateModel> state;        // Необязательное состояние

public:
    // Конструктор класса
    CapabilityModel(CapabilityTypeEnum type, std::optional<StateModel> state = std::nullopt)
        : type(type), state(state) {}

    // Получить тип Capability
    CapabilityTypeEnum getType() const {
        return type;
    }

    // Получить состояние (если оно есть)
    std::optional<StateModel> getState() const {
        return state;
    }

    // Установить состояние (будет использоваться сервисом для обновления состояния)
    void setState(const StateModel& newState) {
        state = newState;
    }

    // Метод для добавления результата действия (если состояние не задано, создается пустое)
    void setActionStatus(const ActionResultModel& actionResult) {
        if (!state.has_value()) {
            state = StateModel("", std::nullopt, std::nullopt);  // Если состояния нет, создаём новое с пустыми значениями
        }
        state->setActionResult(actionResult);  // Обновляем состояние с результатом действия
    }

    // Сериализация объекта в JSON
    void serializeToJson(JsonDocument& doc) const {
        doc["type"] = capabilityTypeToString(type);  // Сериализуем тип capability
        if (state.has_value()) {
            JsonDocument stateDoc;  // Создаём временный документ для сериализации состояния
            state->serializeToJson(stateDoc);  // Сериализуем состояние
            doc["state"] = stateDoc.as<JsonObject>();  // Добавляем состояние в JSON
        }
    }

    // Проверка наличия состояния
    bool hasState() const {
        return state.has_value();  // Проверяем, есть ли состояние
    }
};

#endif // CAPABILITYMODEL_H
