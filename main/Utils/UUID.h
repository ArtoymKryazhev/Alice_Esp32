#ifndef UUID_H
#define UUID_H

#include <Arduino.h>

class UUID {
public:
    // Генерация UUID версии 4
    static String generate() {
        String uuid = "";
        
        // Генерация каждого сегмента UUID
        uuid += String(random(0, 0xffff), HEX);   // Первый сегмент
        uuid += String(random(0, 0xffff), HEX);   // Второй сегмент
        uuid += "-";
        uuid += String(random(0, 0xffff), HEX);   // Третий сегмент (включая версию)
        uuid += "-";
        
        // Четвёртый сегмент, включающий версию (4)
        uuid += String((random(0, 0x0fff) | 0x4000), HEX); 
        uuid += "-";
        
        // Пятый сегмент с определёнными битами для совместимости с RFC 4122
        uuid += String((random(0, 0x3fff) | 0x8000), HEX);
        uuid += "-";
        
        // Генерация последних сегментов с случайными данными
        uuid += String(random(0, 0xffff), HEX);
        uuid += String(random(0, 0xffff), HEX);
        uuid += String(random(0, 0xffff), HEX);
        
        return uuid;
    }
};

#endif // UUID_H
