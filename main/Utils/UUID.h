#ifndef UUID_H
#define UUID_H

#include <Arduino.h>

class UUID {
public:
    // Генерация UUID версии 4 (случайный UUID)
    static String generate() {
        String uuid = "";

        // Генерация первых двух сегментов UUID
        uuid += String(random(0, 0xffff), HEX);   
        uuid += String(random(0, 0xffff), HEX);   
        uuid += "-";

        // Третий сегмент (произвольный)
        uuid += String(random(0, 0xffff), HEX);   
        uuid += "-";

        // Четвёртый сегмент, фиксированный под версию 4 (0x4xxx)
        uuid += String((random(0, 0x0fff) | 0x4000), HEX); 
        uuid += "-";

        // Пятый сегмент, бит 8 и 9 должны быть 10 (0x8xxx)
        uuid += String((random(0, 0x3fff) | 0x8000), HEX);
        uuid += "-";

        // Последние три сегмента UUID (случайные)
        uuid += String(random(0, 0xffff), HEX);
        uuid += String(random(0, 0xffff), HEX);
        uuid += String(random(0, 0xffff), HEX);

        return uuid;
    }
};

#endif // UUID_H
