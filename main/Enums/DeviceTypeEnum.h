#ifndef DEVICE_TYPE_ENUM_H
#define DEVICE_TYPE_ENUM_H

#include <ArduinoJson.h>  // Подключаем библиотеку для работы с JSON

// Определяем перечисление DeviceTypeEnum
enum class DeviceTypeEnum {
    LIGHT,  // Тип устройства: Свет
};

// Функция для преобразования перечисления в строку
const char* deviceTypeToString(DeviceTypeEnum deviceType) {
    switch (deviceType) {
        case DeviceTypeEnum::LIGHT:
            return "LIGHT";
        default:
            return "Unknown";
    }
}

// Функция для сериализации в JSON
void serializeDeviceTypeToJson(DeviceTypeEnum deviceType, JsonDocument& doc) {
    doc["deviceType"] = deviceTypeToString(deviceType);
}

#endif  // DEVICE_TYPE_ENUM_H
