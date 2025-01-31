#ifndef STATEMODEL_H
#define STATEMODEL_H

#include <ArduinoJson.h>
#include <optional>
#include "ActionResultModel.h"  // Используем относительный путь для подключения ActionResultModel

class StateModel {
private:
    String instance;                    // Уникальный идентификатор состояния
    std::optional<ActionResultModel> actionResult;  // Необязательное поле (ActionResultModel)
    std::optional<JsonDocument> value;         // Необязательное поле для значения состояния

public:
    // Конструктор класса
    StateModel(String instance, 
               std::optional<ActionResultModel> actionResult = std::nullopt, 
               std::optional<JsonDocument> value = std::nullopt)
        : instance(instance), actionResult(actionResult), value(value) {}

    // Метод для задания ActionResultModel
    void setActionResult(ActionResultModel actionResult) {
        this->actionResult = actionResult;
    }

    // Метод для сериализации объекта в JSON
    void serializeToJson(JsonDocument& doc) const {
        // Добавляем instance в JSON
        doc["instance"] = instance;

        // Если есть actionResult, добавляем его в JSON
        if (actionResult.has_value()) {
            JsonDocument actionResultDoc;
            actionResult->serializeToJson(actionResultDoc);
            doc["action_result"] = actionResultDoc.as<JsonObject>();
        }

        // Если есть значение value, добавляем его в JSON
        if (value.has_value()) {
            doc["value"] = value.value();
        }
    }

    // Статический метод для создания объекта StateModel из JSON
    static std::optional<StateModel> from(const JsonObject& data) {
        // Переменные для instance и value
        String instance;
        std::optional<JsonDocument> value;

        // Проверяем наличие ключа "instance" и его тип
        if (data["instance"].is<String>()) {
            instance = data["instance"].as<String>();
        } else {
            return std::nullopt; // Если нет или тип неверный, возвращаем пустой результат
        }

        // Проверяем наличие и тип ключа "value"
        if (!data["value"].isNull()) {
            JsonDocument ValueJsonDocument; // Временный документ для хранения значения
            if (data["value"].is<bool>()) {
                ValueJsonDocument.set(data["value"].as<bool>()); // Сохраняем булево значение
            } else if (data["value"].is<String>()) {
                ValueJsonDocument.set(data["value"].as<String>()); // Сохраняем строку
            } else if (data["value"].is<JsonObject>()) {
                ValueJsonDocument.set(data["value"].as<JsonObject>()); // Копируем именованный массив
            } else {
                return std::nullopt; // Если тип не поддерживается, возвращаем пустой результат
            }
            value = ValueJsonDocument; // Сохраняем значение в optional
        }

        // Создаем и возвращаем объект StateModel
        return StateModel(instance, std::nullopt, value);
    }
};

#endif // STATEMODEL_H
