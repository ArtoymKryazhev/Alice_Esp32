#include "Controllers/UserController.h"
#include "Services/NetworkService.h"
#include "Repository/DeviceRepository.h"
#include "Services/PinService.h"

#include <WebServer.h>
#include <ArduinoJson.h>
#include <vector>
#include <Arduino.h>


WebServer server(80);

const char* WIFI_SSID = "bwmax";  
const char* WIFI_PASSWORD = "KabyLake101#";  

void setup() {
    Serial.begin(115200);
    
    NetworkService::connect(WIFI_SSID, WIFI_PASSWORD);

    server.on("/v1.0/user/devices", HTTP_GET, UserController::handleDevicesRequest);
    server.on("/v1.0/user/devices/query", HTTP_POST, UserController::handleDevicesRequest);
    server.on("/v1.0/user/devices/action", HTTP_POST, UserController::handleDevicesRequest);
    server.begin();
    Serial.println("Веб-сервер запущен.");

    PinService::initializeAllPins(DeviceRepository::getAllDevice());
}

void loop() {
    server.handleClient();
}
