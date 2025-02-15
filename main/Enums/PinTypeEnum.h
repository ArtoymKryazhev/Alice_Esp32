#ifndef PIN_ENUMS_H
#define PIN_ENUMS_H

// Режим работы пина
enum class PinModeEnum {
    DIGITAL_INPUT,          // Цифровой вход
    DIGITAL_OUTPUT,         // Цифровой выход
};

// Добавляем метод для получения значения режима пина для Arduino
inline char* getArduinoPinMode(PinModeEnum mode) {
    switch (mode) {
        case PinModeEnum::DIGITAL_INPUT: return "INPUT";             // Цифровой вход
        case PinModeEnum::DIGITAL_OUTPUT: return "OUTPUT";           // Цифровой выход
        default: return "INPUT";                                     // По умолчанию цифровой вход
    }
}


// Состояние пина
enum class PinStateEnum {
    DIGITAL_LOW,  // LOW
    DIGITAL_HIGH, // HIGH
};


// Добавляем метод для получения значения режима пина для Arduino
inline char* getArduinoPinState(PinStateEnum state) {
    switch (state) {
        case PinStateEnum::DIGITAL_LOW: return "LOW";             // Цифровой вход
        case PinStateEnum::DIGITAL_HIGH: return "HIGH";           // Цифровой выход
        default: return "LOW";                                     // По умолчанию цифровой вход
    }
}




#endif // PIN_ENUMS_H
