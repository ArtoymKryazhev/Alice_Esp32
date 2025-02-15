#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include "Models/ResponseModel.h"
#include "Repository/DeviceRepository.h"
#include "Utils/TArray.h"
#include "Models/DeviceModel.h"
#include "Models/ActionResultModel.h"
#include "Services/CapabilityService.h"

#include <ArduinoJson.h>
#include <vector>

class UserService {
public:
    static String processRequest(const String& uri, const JsonObject& dataObject) {
        String responseStr;
        JsonDocument doc;
        
        // Обработка маршрута /v1.0/user/devices и /v1.0/user/devices/query
        if (uri == "/v1.0/user/devices" || uri == "/v1.0/user/devices/query") {
            std::vector<DeviceModel> devices = DeviceRepository::getAllDevice();
            ResponseModel response(devices);
            response.serializeToJson(doc);
            serializeJson(doc, responseStr);
        } 
        // Обработка маршрута /v1.0/user/devices/action
        else if (uri == "/v1.0/user/devices/action" && dataObject.size() > 0) {
            JsonVariant devicesVariant = TArray::getValueByDotNotation(dataObject, "payload.devices");

            if (!devicesVariant.is<JsonArray>()) {
                return "{\"error\": \"Devices are not an array\"}";
            }

            JsonArray devices = devicesVariant.as<JsonArray>();
            if (devices.size() == 0) {
                return "{\"error\": \"No devices found\"}";
            }

            std::vector<DeviceModel> resultDevices;
            for (const JsonObject& deviceData : devices) {
                if (deviceData["id"].is<const char*>()) {
                    String id = deviceData["id"].as<String>();
                    std::string stdId = id.c_str();

                    std::optional<DeviceModel> device = DeviceRepository::getDeviceById(stdId);
                    if (device) {
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
                    }
                }
            }

            ResponseModel responseModel(resultDevices);
            responseModel.serializeToJson(doc);
            serializeJson(doc, responseStr);
        } 
        // Обработка маршрута по умолчанию (если ничего не найдено)
        else {
            return "{\"error\": \"Not Found\"}";
        }

        return responseStr;
    }
};

#endif
