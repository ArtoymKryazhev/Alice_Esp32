#ifndef TARRAY_H
#define TARRAY_H

#include <ArduinoJson.h>  // Подключаем библиотеку для работы с JSON

class TArray {
public:
    // Статическая функция для извлечения значения по точечной нотации
    static JsonVariant getValueByDotNotation(JsonObject& obj, const String& path, JsonVariant defaultValue = JsonVariant()) {
        int startIdx = 0;
        String key;

        // Начинаем с корневого объекта
        JsonVariant currentValue = obj;

        // Проходим по каждой части пути
        while (startIdx < path.length()) {
            int dotIdx = path.indexOf('.', startIdx);

            // Вычисляем текущий ключ
            if (dotIdx == -1) {
                key = path.substring(startIdx);  // Последний сегмент пути
                startIdx = path.length();       // Выходим из цикла
            } else {
                key = path.substring(startIdx, dotIdx);  // Текущий сегмент пути
                startIdx = dotIdx + 1;
            }

            // Проверяем, является ли текущий элемент JsonObject
            if (!currentValue.is<JsonObject>()) {
                return defaultValue;  // Если текущий объект не является JsonObject, возвращаем значение по умолчанию
            }

            JsonObject currentObject = currentValue.as<JsonObject>();

            // Если ключ отсутствует, возвращаем значение по умолчанию
            if (!currentObject[key]) {
                return defaultValue;
            }

            // Переходим к следующему значению
            currentValue = currentObject[key];
        }

        // Возвращаем найденное значение
        return currentValue;
    }
};

#endif // TARRAY_H
