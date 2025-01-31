#ifndef ERROR_CODE_ENUM_H
#define ERROR_CODE_ENUM_H

#include <ArduinoJson.h>  // Подключаем библиотеку для работы с JSON

// Определяем перечисление ErrorCodeEnum
enum class ErrorCodeEnum {
    DEVICE_OFF
};

// Функция для преобразования перечисления в строку
const char* errorCodeToString(ErrorCodeEnum errorCode) {
    switch (errorCode) {
        case ErrorCodeEnum::DEVICE_OFF:
            return "DEVICE_OFF";
        default:
            return "Unknown";
    }
}

// Функция для сериализации в JSON
void serializeErrorCodeToJson(ErrorCodeEnum errorCode, JsonDocument& doc) {
    doc["errorCode"] = errorCodeToString(errorCode);
}

#endif  // ERROR_CODE_ENUM_H
