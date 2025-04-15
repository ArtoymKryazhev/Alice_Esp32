#ifndef ERROR_CODE_ENUM_H
#define ERROR_CODE_ENUM_H

#include <ArduinoJson.h>  // Подключаем библиотеку для работы с JSON

// Перечисление для хранения кодов ошибок, поддерживаемых Яндекс Алисой
enum class ErrorCodeEnum {
    DEVICE_OFF,        // Устройство выключено
    INVALID_ACTION,    // Недопустимое действие
    INVALID_VALUE,     // Недопустимое значение
    INTERNAL_ERROR     // Неизвестная внутренняя ошибка
};

// Преобразование кода ошибки в строку (для Алисы)
const char* errorCodeToString(ErrorCodeEnum errorCode) {
    switch (errorCode) {
        case ErrorCodeEnum::DEVICE_OFF:
            return "DEVICE_OFF"; // Устройство выключено
        case ErrorCodeEnum::INVALID_ACTION:
            return "INVALID_ACTION"; // Недопустимое действие
        case ErrorCodeEnum::INVALID_VALUE:
            return "INVALID_VALUE"; // Недопустимое значение
        case ErrorCodeEnum::INTERNAL_ERROR:
            return "INTERNAL_ERROR"; // Неизвестная внутренняя ошибка
        default:
            return "Unknown";  // Фолбэк на случай некорректного значения
    }
}

// Сериализация кода ошибки в JSON
void serializeErrorCodeToJson(ErrorCodeEnum errorCode, JsonDocument& doc) {
    doc["error_code"] = errorCodeToString(errorCode);  // Алиса ожидает поле "error_code"
}

#endif  // ERROR_CODE_ENUM_H
