#ifndef ERROR_CODE_ENUM_H
#define ERROR_CODE_ENUM_H

#include <ArduinoJson.h>  // Подключаем библиотеку для работы с JSON

// Определяем перечисление ErrorCodeEnum, которое будет хранить коды ошибок для устройств
enum class ErrorCodeEnum {
    DEVICE_OFF  // Ошибка: устройство выключено
};

// Функция для преобразования ErrorCodeEnum в строковое представление
const char* errorCodeToString(ErrorCodeEnum errorCode) {
    switch (errorCode) {
        case ErrorCodeEnum::DEVICE_OFF:
            return "DEVICE_OFF";  // Возвращаем строку, соответствующую коду ошибки
        default:
            return "Unknown";  // По умолчанию, если код не найден
    }
}

// Функция для сериализации ErrorCodeEnum в JSON
void serializeErrorCodeToJson(ErrorCodeEnum errorCode, JsonDocument& doc) {
    doc["errorCode"] = errorCodeToString(errorCode);  // Добавляем строку ошибки в JSON документ
}

#endif  // ERROR_CODE_ENUM_H
