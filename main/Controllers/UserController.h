#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "Models/ResponseModel.h"
#include "Repository/DeviceRepository.h"
#include "Services/CapabilityService.h"
#include "Utils/TArray.h"

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
            String body = server.arg("plain");

            DeserializationError error = deserializeJson(dataDoc, body);
            if (error) {
                server.send(400, "application/json", "{\"error\": \"Invalid JSON\"}");
                return;
            }

            dataObject = dataDoc.as<JsonObject>();
            serializeJson(dataObject, Serial);
        }

        String uri = server.uri();

        if (uri == "/v1.0/user/devices" || uri == "/v1.0/user/devices/query") {
            std::vector<DeviceModel> devices = DeviceRepository::getAllDevices();
            JsonDocument doc;
            ResponseModel response(devices);
            response.serializeToJson(doc);

            serializeJson(doc, Serial);
            String responseStr;
            serializeJson(doc, responseStr);
            server.send(200, "application/json", responseStr);
            return;
        }

        if (uri == "/v1.0/user/devices/action" && dataObject.size() > 0) {
            JsonVariant devicesVariant = TArray::getValueByDotNotation(dataObject, "payload.devices");

            if (!devicesVariant.is<JsonArray>()) {
                server.send(400, "application/json", "{\"error\": \"Devices are not an array\"}");
                return;
            }

            JsonArray devices = devicesVariant.as<JsonArray>();
            if (devices.size() == 0) {
                server.send(400, "application/json", "{\"error\": \"No devices found\"}");
                return;
            }

            std::vector<DeviceModel> resultDevices;

            for (const JsonObject& deviceData : devices) {
                if (deviceData["id"].is<const char*>()) {
                    String id = deviceData["id"].as<String>();
                    std::string stdId = id.c_str();

                    std::optional<DeviceModel> device = DeviceRepository::getDeviceById(stdId);

                    if (device) {
                        Serial.println("Устройство найдено: " + id);

                        JsonDocument JsonDocumentCapabilities;
                        JsonArray JsonArrayCapabilities = JsonDocumentCapabilities.to<JsonArray>();

                        CapabilityService::fromBatch(deviceData["capabilities"], JsonArrayCapabilities);

                        for (const JsonObject& capability : JsonArrayCapabilities) {
                            CapabilityModel* deviceCapability = device->getCapabilityByType(capability["type"].as<String>());
                            if (deviceCapability != nullptr) {
                                ActionResultModel actionResult(ActionResultStatusEnum::DONE);
                                CapabilityService::setActionStatus(*deviceCapability, "on", actionResult);

                                resultDevices.push_back(*device);
                            }
                        }
                    } else {
                        Serial.println("Устройство не найдено: " + id);
                    }
                } else {
                    Serial.println("ID устройства отсутствует или некорректен");
                }
            }

            ResponseModel responseModel(resultDevices);
            JsonDocument ResultDeviceJsonDocument;
            responseModel.serializeToJson(ResultDeviceJsonDocument);

            serializeJson(ResultDeviceJsonDocument, Serial);
            String responseString;
            serializeJson(ResultDeviceJsonDocument, responseString);
            server.send(200, "application/json", responseString);
            return;
        }

        server.send(404, "text/plain", "Not Found");
    }
};

#endif
