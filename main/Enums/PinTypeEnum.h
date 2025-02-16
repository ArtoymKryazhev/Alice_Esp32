#ifndef PIN_ENUMS_H
#define PIN_ENUMS_H

#include <stdint.h>

// Режим работы пина. Задаем базовый тип uint8_t для корректного преобразования
enum class PinModeEnum : uint8_t {
DIGITAL_INPUT = 0, // Цифровой вход (аналог макроса INPUT)
DIGITAL_OUTPUT = 1 // Цифровой выход (аналог макроса OUTPUT)
};

// Функция для получения значения режима пина для Arduino.
// static_cast используется для явного преобразования типа enum в uint8_t.
inline constexpr uint8_t getArduinoPinMode(PinModeEnum mode) {
return static_cast<uint8_t>(mode);
}

// Состояние пина. Тоже задаем базовый тип uint8_t
enum class PinStateEnum : uint8_t {
DIGITAL_LOW = 0, // Низкий уровень (аналог LOW)
DIGITAL_HIGH = 1 // Высокий уровень (аналог HIGH)
};

// Функция для получения значения состояния пина для Arduino.
inline constexpr uint8_t getArduinoPinState(PinStateEnum state) {
return static_cast<uint8_t>(state);
}

#endif // PIN_ENUMS_H