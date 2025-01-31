#ifndef ACTION_RESULT_STATUS_ENUM_H
#define ACTION_RESULT_STATUS_ENUM_H

#include <ArduinoJson.h>  // Для работы с JSON

// Определение перечисления ActionResultStatusEnum
// Используется для описания статуса результата действия
enum class ActionResultStatusEnum {
    DONE,    // Действие выполнено успешно
    ERROR,   // Произошла ошибка при выполнении действия
    UNKNOWN  // Статус неопределён
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
// Сохраняет статус в объекте JSON
void serializeActionResultStatusToJson(ActionResultStatusEnum status, JsonDocument& doc) {
    doc["status"] = actionResultStatusToString(status);
}

#endif // ACTION_RESULT_STATUS_ENUM_H
