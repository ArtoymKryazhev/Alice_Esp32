#ifndef TARRAY_H
#define TARRAY_H

#include <ArduinoJson.h>  // Подключаем библиотеку для работы с JSON

class TArray {
public:
    // Статическая функция для извлечения значения по точечной нотации
    // path - путь к значению в виде строки, разделённой точками.
    // defaultValue - значение, которое будет возвращено, если путь не существует.
    static JsonVariant getValueByDotNotation(const JsonObject& obj, const String& path, JsonVariant defaultValue = JsonVariant()) {
        int startIdx = 0;  // Индекс начала пути
        String key;        // Ключ для текущего сегмента пути

        // Начинаем с корневого объекта
        JsonVariant currentValue = obj;

        // Проходим по каждой части пути
        while (startIdx < path.length()) {
            int dotIdx = path.indexOf('.', startIdx);  // Ищем разделитель точкой

            // Если точка не найдена, значит, это последний сегмент пути
            if (dotIdx == -1) {
                key = path.substring(startIdx);  // Последний сегмент пути
                startIdx = path.length();        // Выход из цикла
            } else {
                key = path.substring(startIdx, dotIdx);  // Текущий сегмент пути
                startIdx = dotIdx + 1;  // Обновляем индекс начала для следующего сегмента
            }

            // Проверяем, является ли текущий элемент объектом JsonObject
            if (!currentValue.is<JsonObject>()) {
                return defaultValue;  // Если текущий элемент не объект, возвращаем значение по умолчанию
            }

            JsonObject currentObject = currentValue.as<JsonObject>();  // Преобразуем в объект

            // Если ключ отсутствует в текущем объекте, возвращаем значение по умолчанию
            if (!currentObject[key]) {
                return defaultValue;
            }

            // Переходим к следующему значению по ключу
            currentValue = currentObject[key];
        }

        // Возвращаем найденное значение
        return currentValue;
    }
};

#endif // TARRAY_H
