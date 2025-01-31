#ifndef CAPABILITY_TYPE_ENUM_H
#define CAPABILITY_TYPE_ENUM_H

#include <ArduinoJson.h>  // Подключаем библиотеку для работы с JSON
#include <string>
#include <optional>

// Определяем перечисление CapabilityTypeEnum
enum class CapabilityTypeEnum {
    ON_OFF,
    RANGE,
    UNKNOWN
};

// Функция для преобразования перечисления в строку
const String capabilityTypeToString(CapabilityTypeEnum capability) {
    switch (capability) {
        case CapabilityTypeEnum::ON_OFF:
            return "devices.capabilities.on_off";
        case CapabilityTypeEnum::RANGE:
            return "devices.capabilities.color_setting";
        case CapabilityTypeEnum::UNKNOWN:
            return "Unknown";
        default:
            return "Unknown";
    }
}

// Функция для преобразования строки в перечисление
static CapabilityTypeEnum fromCapabilityTypeEnum(const JsonObject& data) {
    if (data["type"] == capabilityTypeToString(CapabilityTypeEnum::ON_OFF)) {
        return CapabilityTypeEnum::ON_OFF;
    } else if (data["type"] == capabilityTypeToString(CapabilityTypeEnum::RANGE)) {
        return CapabilityTypeEnum::RANGE;
    } else {
        return CapabilityTypeEnum::UNKNOWN;
    }
}

// Функция для сериализации в JSON
void serializeCapabilityTypeToJson(CapabilityTypeEnum capability, JsonDocument& doc) {
    doc["capability"] = capabilityTypeToString(capability);
}

#endif  // CAPABILITY_TYPE_ENUM_H
