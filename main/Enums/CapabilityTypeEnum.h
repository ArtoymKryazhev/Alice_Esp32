#ifndef CAPABILITY_TYPE_ENUM_H
#define CAPABILITY_TYPE_ENUM_H

#include <ArduinoJson.h>  // Подключаем библиотеку для работы с JSON
#include <string>
#include <optional>

// Определяем перечисление CapabilityTypeEnum для типов способностей
enum class CapabilityTypeEnum {
    ON_OFF,   // Способность для включения/выключения
    RANGE,    // Способность для настройки диапазона (например, яркость, температура)
    UNKNOWN   // Неизвестная способность
};

// Функция для преобразования перечисления в строку
const String capabilityTypeToString(CapabilityTypeEnum capability) {
    switch (capability) {
        case CapabilityTypeEnum::ON_OFF:
            return "devices.capabilities.on_off";  // Строковое представление способности "включение/выключение"
        case CapabilityTypeEnum::RANGE:
            return "devices.capabilities.color_setting";  // Строковое представление способности "диапазон"
        case CapabilityTypeEnum::UNKNOWN:
            return "Unknown";  // Если способность неизвестна
        default:
            return "Unknown";  // Если тип не определён
    }
}

// Функция для преобразования строки в перечисление CapabilityTypeEnum
static CapabilityTypeEnum fromCapabilityTypeEnum(const JsonObject& data) {
    if (data["type"] == capabilityTypeToString(CapabilityTypeEnum::ON_OFF)) {
        return CapabilityTypeEnum::ON_OFF;  // Если тип соответствует ON_OFF
    } else if (data["type"] == capabilityTypeToString(CapabilityTypeEnum::RANGE)) {
        return CapabilityTypeEnum::RANGE;  // Если тип соответствует RANGE
    } else {
        return CapabilityTypeEnum::UNKNOWN;  // В случае неизвестного типа
    }
}

// Функция для сериализации типа способности в JSON
void serializeCapabilityTypeToJson(CapabilityTypeEnum capability, JsonDocument& doc) {
    doc["capability"] = capabilityTypeToString(capability);  // Сохраняем строковое представление типа способности в JSON документ
}

#endif  // CAPABILITY_TYPE_ENUM_H
