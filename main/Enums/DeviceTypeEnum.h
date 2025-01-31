#ifndef DEVICE_TYPE_ENUM_H
#define DEVICE_TYPE_ENUM_H

#include <ArduinoJson.h>  // Подключаем библиотеку для работы с JSON

// Определяем перечисление DeviceTypeEnum для типов устройств
enum class DeviceTypeEnum {
    LIGHT,  // Тип устройства: Свет
};

// Функция для преобразования перечисления в строку
const char* deviceTypeToString(DeviceTypeEnum deviceType) {
    switch (deviceType) {
        case DeviceTypeEnum::LIGHT:
            return "LIGHT";  // Возвращаем строковое представление типа устройства
        default:
            return "Unknown";  // Если тип устройства неизвестен, возвращаем "Unknown"
    }
}

// Функция для сериализации типа устройства в JSON
void serializeDeviceTypeToJson(DeviceTypeEnum deviceType, JsonDocument& doc) {
    doc["deviceType"] = deviceTypeToString(deviceType);  // Сохраняем строковое представление типа устройства в JSON документ
}

#endif  // DEVICE_TYPE_ENUM_H
