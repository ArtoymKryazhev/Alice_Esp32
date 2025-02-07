#ifndef REQUEST_SERVICE_H
#define REQUEST_SERVICE_H

#include <ArduinoJson.h>
#include <WebServer.h>

class RequestService {
public:
    static bool parseJsonRequest(WebServer& server, JsonDocument& doc) {
        String body = server.arg("plain");

        DeserializationError error = deserializeJson(doc, body);
        if (error) {
            Serial.println("Ошибка парсинга JSON");
            return false;
        }

        return true;
    }
};

#endif
