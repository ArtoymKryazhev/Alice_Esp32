#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "Models/ResponseModel.h"
#include "Repository/DeviceRepository.h"
#include "Services/CapabilityService.h"
#include "Services/RequestService.h"
#include "Utils/TArray.h"
#include "Services/UserService.h"  // Подключаем UserService

#include <WebServer.h>
#include <ArduinoJson.h>
#include <vector>
#include <Arduino.h>

extern WebServer server;  // Используем сервер, объявленный в main.ino

class UserController {
public:
    static void handleDevicesRequest() {
        JsonDocument dataDoc;
        JsonObject dataObject;

        if (server.method() == HTTP_POST) {
            if (!RequestService::parseJsonRequest(server, dataDoc)) {
                server.send(400, "application/json", "{\"error\": \"Invalid JSON\"}");
                return;
            }

            dataObject = dataDoc.as<JsonObject>();  
        }

        String uri = server.uri();
        
        // Отправляем запрос на обработку в UserService
        String responseStr = UserService::processRequest(uri, dataObject);

        // Отправляем ответ
        server.send(200, "application/json", responseStr);
    }
};

#endif
