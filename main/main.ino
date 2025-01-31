#include "connectToWiFi.h"

#include "Utils/TArray.h"
#include "Utils/UUID.h"

#include "Models/ActionResultModel.h"
#include "Models/CapabilityModel.h"
#include "Models/DeviceInfoModel.h"
#include "Models/DeviceModel.h"
#include "Models/ResponseModel.h"
#include "Models/StateModel.h"

#include "Enums/ActionResultStatusEnum.h"
#include "Enums/CapabilityTypeEnum.h"
#include "Enums/DeviceTypeEnum.h"

#include "Services/CapabilityService.h"

#include "Repository/DeviceRepository.h"


#include <WebServer.h>
#include <ArduinoJson.h>
#include <vector>
#include <Arduino.h>

WebServer server(80);

// Константы для имени сети и пароля
const char* WIFI_SSID = "bwmax";  // Имя сети Wi-Fi
const char* WIFI_PASSWORD = "KabyLake101#";  // Пароль Wi-Fi

/**
 * @brief Обработчик для запросов на /v1.0/user/devices, /v1.0/user/devices/query и /v1.0/user/devices/action.
 */
void handleDevicesRequest() {
    JsonDocument dataDoc;
    JsonObject dataObject;

    // Обработка POST-запросов (получаем JSON-данные из тела запроса)
    if (server.method() == HTTP_POST) {
        String body = server.arg("plain");

        // Десериализуем JSON
        DeserializationError error = deserializeJson(dataDoc, body);
        if (error) {
            server.send(400, "application/json", "{\"error\": \"Invalid JSON\"}");
            return;
        }

        dataObject = dataDoc.as<JsonObject>();
        serializeJson(dataObject, Serial);  // Логируем JSON в Serial Monitor
    }

    // Определяем, какой запрос пришел
    String uri = server.uri();

    // 1. Запрос списка устройств или состояния устройств
    if (uri == "/v1.0/user/devices" || uri == "/v1.0/user/devices/query") {
        std::vector<DeviceModel> devices = DeviceRepository::getAllDevices();
        JsonDocument doc;
        ResponseModel response(devices);
        response.serializeToJson(doc);

        serializeJson(doc, Serial);  // Логируем ответ
        String responseStr;
        serializeJson(doc, responseStr);
        server.send(200, "application/json", responseStr);
    }

    // 2. Запрос на выполнение действия с устройствами
    else if (uri == "/v1.0/user/devices/action" && dataObject.size() > 0) {
        // Извлекаем массив устройств из JSON
        JsonVariant devicesVariant = TArray::getValueByDotNotation(dataObject, "payload.devices");

        // Проверяем, что devices является массивом
        if (!devicesVariant.is<JsonArray>()) {
            server.send(400, "application/json", "{\"error\": \"Devices are not an array\"}");
            return;
        }

        JsonArray devices = devicesVariant.as<JsonArray>();

        // Проверяем, что массив устройств не пуст
        if (devices.size() == 0) {
            server.send(400, "application/json", "{\"error\": \"No devices found\"}");
            return;
        }

        std::vector<DeviceModel> resultDevices;

        // Перебираем устройства из запроса
        for (const JsonObject& deviceData : devices) {
            // Проверяем, есть ли поле "id" и является ли оно строкой
            if (deviceData["id"].is<const char*>()) {
                String id = deviceData["id"].as<String>();
                std::string stdId = id.c_str();  // Преобразуем String в std::string

                // Ищем устройство по ID
                std::optional<DeviceModel> device = DeviceRepository::getDeviceById(stdId);

                if (device != std::nullopt) {  // Если устройство найдено
                    Serial.println("Устройство найдено: " + id);

                    // Создаем JSON-массив для хранения способностей устройства
                    JsonDocument JsonDocumentCapabilities;
                    JsonArray JsonArrayCapabilities = JsonDocumentCapabilities.to<JsonArray>();

                    // Извлекаем способности устройства из JSON-запроса
                    CapabilityService::fromBatch(deviceData["capabilities"], JsonArrayCapabilities);

                    // Перебираем все способности устройства
                    for (const JsonObject& capability : JsonArrayCapabilities) {
                        // Проверяем, существует ли запрашиваемая способность у устройства
                        if (device.value().getCapabilityByType(capability["type"].as<String>()) != nullptr) {
                            CapabilityModel* deviceCapability = device.value().getCapabilityByType(capability["type"].as<String>());

                            // Устанавливаем статус действия (например, включение устройства)
                            ActionResultModel actionResult(ActionResultStatusEnum::DONE);
                            CapabilityService::setActionStatus(*deviceCapability, "on", actionResult);

                            // Добавляем устройство в список обработанных устройств
                            resultDevices.push_back(device.value());
                        }
                    }
                } else {
                    Serial.println("Устройство не найдено: " + id);
                }
            } else {
                Serial.println("ID устройства отсутствует или некорректен");
            }
        }

        // Формируем JSON-ответ
        ResponseModel responseModel(resultDevices);
        JsonDocument ResultDeviceJsonDocument;
        responseModel.serializeToJson(ResultDeviceJsonDocument);

        serializeJson(ResultDeviceJsonDocument, Serial);  // Логируем ответ
        String responseString;
        serializeJson(ResultDeviceJsonDocument, responseString);
        server.send(200, "application/json", responseString);
    }

    // 3. Неизвестный запрос — отправляем 404
    else {
        server.send(404, "text/plain", "Not Found");
    }
}

/**
 * @brief Настройка ESP32, подключение к Wi-Fi и запуск веб-сервера.
 */
void setup() {
    Serial.begin(115200);

    // Подключаемся к Wi-Fi
    connectToWiFi(WIFI_SSID, WIFI_PASSWORD);

    // Регистрируем обработчики запросов
    server.on("/v1.0/user/devices", HTTP_GET, handleDevicesRequest);
    server.on("/v1.0/user/devices/query", HTTP_GET, handleDevicesRequest);
    server.on("/v1.0/user/devices/action", HTTP_POST, handleDevicesRequest);

    // Запускаем сервер
    server.begin();
    Serial.println("Веб-сервер запущен.");
}

/**
 * @brief Основной цикл обработки HTTP-запросов.
 */
void loop() {
    server.handleClient();
}
