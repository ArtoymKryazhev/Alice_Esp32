#ifndef PIN_ENUMS_H
#define PIN_ENUMS_H

// Режим работы пина
enum class PinModeEnum {
    DIGITAL_INPUT,          // Цифровой вход
    DIGITAL_OUTPUT,         // Цифровой выход
};

// Состояние пина
enum class PinStateEnum {
    DIGITAL_LOW,  // LOW
    DIGITAL_HIGH, // HIGH
};



// Добавляем метод для получения значения режима пина для Arduino
inline int getArduinoPinMode(PinModeEnum mode) {
    switch (mode) {
        case PinModeEnum::DIGITAL_INPUT: return INPUT;             // Цифровой вход
        case PinModeEnum::DIGITAL_OUTPUT: return OUTPUT;           // Цифровой выход
        default: return INPUT;                                     // По умолчанию цифровой вход
    }
}

inline int getPinState(PinStateEnum state) {
    switch (state) {
        case PinStateEnum::DIGITAL_LOW: return LOW;  // LOW
        case PinStateEnum::DIGITAL_HIGH: return HIGH; // HIGH
        default: return LOW;  // По умолчанию LOW
    }
}



#endif // PIN_ENUMS_H
