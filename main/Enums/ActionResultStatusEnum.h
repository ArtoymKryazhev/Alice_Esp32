#ifndef ACTION_RESULT_STATUS_ENUM_H
#define ACTION_RESULT_STATUS_ENUM_H

#include <ArduinoJson.h>  // Для работы с JSON

// Определение перечисления ActionResultStatusEnum
enum class ActionResultStatusEnum {
    DONE,
    ERROR,
    UNKNOWN
};

// Функция для преобразования enum в строку
const char* actionResultStatusToString(ActionResultStatusEnum status) {
    switch (status) {
        case ActionResultStatusEnum::DONE:
            return "DONE";
        case ActionResultStatusEnum::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

// Функция для сериализации в JSON
void serializeActionResultStatusToJson(ActionResultStatusEnum status, JsonDocument& doc) {
    doc["status"] = actionResultStatusToString(status);
}

#endif // ACTION_RESULT_STATUS_ENUM_H
