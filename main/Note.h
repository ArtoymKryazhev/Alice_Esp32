// #include "connectToWiFi.h"
// #include "Utils/TArray.h"
// #include "Utils/UUID.h"
// #include <WebServer.h>
// #include <ArduinoJson.h>

// WebServer server(80);

// // Константы для имени сети и пароля
// const char* WIFI_SSID = "bwmax"; //Test bwmax
// const char* WIFI_PASSWORD = "KabyLake101#"; //12345678 KabyLake101#

// // Обработчик для запросов на /v1.0/user/devices и /v1.0/user/devices/query
// void handleDevicesRequest() {
//   // Получаем тело запроса (для POST-запросов)
//   if (server.method() == HTTP_POST) {
//     String body = server.arg("plain");

//     // Создаем объект для парсинга JSON
//     StaticJsonDocument<1024> doc;

//     // Парсим JSON  
//     DeserializationError error = deserializeJson(doc, body);

//     if (error) {
//       // Если ошибка при парсинге
//       server.send(400, "application/json", "{\"error\": \"Invalid JSON\"}");
//       return;
//     }

//     // Извлекаем устройства из JSON
//     JsonObject root = doc.as<JsonObject>();

//     JsonVariant result = TArray::getValueByDotNotation(root, "payload.devices");

//     if (!result.isNull()) {
//       Serial.println(result.as<String>()); // Корректное преобразование значения в строку
//     } else {
//       Serial.println("Key not found");
//     }
//   }

//   // Получаем URI запроса
//   String uri = server.uri();  

//   // Логика для обработки различных URI
//   if (uri == "/v1.0/user/devices" || uri == "/v1.0/user/devices/query") {
//     // Отправляем успешный ответ
//     String response = "{\"status\": \"success\"}";
//     server.send(200, "application/json", response);
//   } else {
//     // Если запрос не распознан, возвращаем 404
//     server.send(404, "text/plain", "Not Found");
//   }
// }

// void setup() {
//   Serial.begin(115200);

//   // Подключение к Wi-Fi
//   connectToWiFi(WIFI_SSID, WIFI_PASSWORD);

//   // Регистрируем обработчики запросов
//   server.on("/v1.0/user/devices", HTTP_GET, handleDevicesRequest);
//   server.on("/v1.0/user/devices/query", HTTP_POST, handleDevicesRequest);

//   // Запускаем сервер
//   server.begin();
//   Serial.println("Веб-сервер запущен.");

//   String myUUID = UUID::generate();
  
//   // Печать UUID в Serial Monitor
//   Serial.println(myUUID);
// }

// void loop() {
//   // Обработка запросов
//   server.handleClient();
// }















// #include "connectToWiFi.h"

// #include "Utils/TArray.h"

// #include "Models/ActionResultModel.h"
// #include "Models/CapabilityModel.h"
// #include "Models/DeviceInfoModel.h"
// #include "Models/DeviceModel.h"
// //#include "Models/ResponseModel.h"
// #include "Models/StateModel.h"

// #include "Enums/ActionResultStatusEnum.h"
// #include "Enums/CapabilityTypeEnum.h"
// #include "Enums/DeviceTypeEnum.h"

// #include <WebServer.h>
// #include <ArduinoJson.h>
// #include <vector>

// WebServer server(80);

// using namespace std;

// // Константы для имени сети и пароля
// const char* WIFI_SSID = "bwmax"; //Test bwmax
// const char* WIFI_PASSWORD = "KabyLake101#"; //12345678 KabyLake101#

// // Обработчик для запросов на /v1.0/user/devices и /v1.0/user/devices/query
// void handleDevicesRequest() {
//   // Получаем тело запроса (для POST-запросов)
//   if (server.method() == HTTP_POST) {
//     String body = server.arg("plain");

//     // Создаем объект для парсинга JSON
//     JsonDocument doc;

//     // Парсим JSON  
//     DeserializationError error = deserializeJson(doc, body);

//     // Выводим результат в Serial Monitor
//     serializeJsonPretty(doc, Serial);

//     if (error) {
//       // Если ошибка при парсинге
//       server.send(400, "application/json", "{\"error\": \"Invalid JSON\"}");
//       return;
//     }
//   }

//   // Получаем URI запроса
//   String uri = server.uri();  

//   // Логика для обработки различных URI
//   if (uri == "/v1.0/user/devices" || uri == "/v1.0/user/devices/query") {
//     // Отправляем успешный ответ
//     String response = "{\"status\": \"success\"}";
//     server.send(200, "application/json", response);
//   } else {
//     // Если запрос не распознан, возвращаем 404
//     server.send(404, "text/plain", "Not Found");
//   }
// }

// void setup() {
//   Serial.begin(115200);

//   // Подключение к Wi-Fi
//   connectToWiFi(WIFI_SSID, WIFI_PASSWORD);

//   // Регистрируем обработчики запросов
//   server.on("/v1.0/user/devices", HTTP_GET, handleDevicesRequest);
//   server.on("/v1.0/user/devices/query", HTTP_POST, handleDevicesRequest);

//   // Запускаем сервер
//   server.begin();
//   Serial.println("Веб-сервер запущен.");

//   // ActionResultModel result(ActionResultStatusEnum::DONE, ErrorCodeEnum::DEVICE_OFF, "foo");
//   // ActionResultModel result1(ActionResultStatusEnum::DONE, std::nullopt, "foo");

//   // // Создаем экземпляр StateModel с actionResult
//   // StateModel state("State1", result, "Active");
//   // state.setActionResult(result1);

//   // CapabilityModel capability(CapabilityTypeEnum::ON_OFF);
//   // capability.setActionStatus("on", result1);

//   // DeviceInfoModel deviceWithVersions("manufacturer", "model", std::nullopt);

//   // //Сериализация state в JSON
//   // JsonDocument doc;
//   // deviceWithVersions.serializeToJson(doc);

//   // // Выводим сериализованный JSON
//   // serializeJson(doc, Serial);
//   // Serial.println();

//   // vector<CapabilityModel> capabilities = {CapabilityModel(CapabilityTypeEnum::ON_OFF)};
//   // DeviceInfoModel deviceInfo("Manufacturer", "Model", "1.0", "2.0");

//   // // Создаем объект DeviceModel
//   // DeviceModel device(
//   //     "light-diod-1", 
//   //     "Светодиод 1", 
//   //     DeviceTypeEnum::LIGHT, 
//   //     capabilities, 
//   //     deviceInfo, 
//   //     "Описание устройства"
//   // );

//   //   // Создаем документ JSON для сериализации
//   //   JsonDocument doc;

//   //   // Сериализуем объект в JSON
//   //   device.serializeToJson(doc);

//   //   // Выводим результат в Serial Monitor
//   //   serializeJsonPretty(doc, Serial);
// }

// void loop() {
//   // Обработка запросов
//   server.handleClient();
// }




// #ifndef DEVICE_MODEL_H
// #define DEVICE_MODEL_H

// #include <ArduinoJson.h>
// #include <vector>
// #include <optional>
// #include "C:/Dev/Edu/Arduino/Test/main/Enums/CapabilityTypeEnum.h"
// #include "C:/Dev/Edu/Arduino/Test/main/Enums/DeviceTypeEnum.h"
// #include "DeviceInfoModel.h"
// #include "CapabilityModel.h"

// using namespace std;  // Упрощение использования типов из std

// class DeviceModel {
// private:
//     string id;
//     string name;
//     vector<CapabilityModel> capabilities;
//     DeviceTypeEnum type;
//     optional<DeviceInfoModel> deviceInfo;
//     optional<string> description; // Сделаем описание опциональным

// public:
//     // Конструктор с обязательными параметрами и необязательными с дефолтными значениями
//     DeviceModel(const string& id, const string& name, DeviceTypeEnum type,
//                 const vector<CapabilityModel>& capabilities, 
//                 optional<DeviceInfoModel> deviceInfo = nullopt, 
//                 optional<string> description = nullopt)
//         : id(id), name(name), capabilities(capabilities), type(type), deviceInfo(deviceInfo), description(description) {}

//     // Получить Capability по типу
//     CapabilityModel* getCapabilityByType(CapabilityTypeEnum type) {
//         for (auto& capability : capabilities) {
//             if (capability.getType() == type) {
//                 return &capability;
//             }
//         }
//         return nullptr;
//     }

//     // Сериализация в JSON
//     void DeviceModel::serializeToJson(JsonObject& doc) const {
//       doc["id"] = id;
//       doc["name"] = name;
//       doc["type"] = deviceTypeToString(type);

//       // Создание массива capabilities
//       JsonArray capabilitiesArray = doc.createNestedArray("capabilities");
//       for (const auto& capability : capabilities) {
//           JsonObject capabilityJson = capabilitiesArray.add<JsonObject>();
//           capability.serializeToJson(capabilityJson);
//       }

//       // Добавляем описание, если оно существует
//       if (description.has_value()) {
//           doc["description"] = description.value();
//       }

//       // Сериализация deviceInfo, если оно существует
//       if (deviceInfo) {
//           JsonObject deviceInfoJson = doc.add<JsonObject>("device_info");
//           deviceInfo->serializeToJson(deviceInfoJson);
//       }
//     }
//   }

//     // Статический метод для получения устройств
//     static vector<DeviceModel> getDevices() {
//         vector<DeviceModel> devices;

//         vector<CapabilityModel> capabilities = {
//             CapabilityModel(CapabilityTypeEnum::ON_OFF)
//         };

//         DeviceInfoModel deviceInfo("manufacturer", "model", "1.0", "1.0");

//         devices.push_back(DeviceModel(
//             "light-diod-1", "Светодиод 1", DeviceTypeEnum::LIGHT, capabilities, deviceInfo
//         ));

//         devices.push_back(DeviceModel(
//             "light-diod-2", "Светодиод 2", DeviceTypeEnum::LIGHT, capabilities, deviceInfo
//         ));

//         return devices;
//     }

//     // Статический метод для получения устройства по ID
//     static DeviceModel* getDeviceById(const string& id) {
//         static vector<DeviceModel> devices = getDevices();
//         for (auto& device : devices) {
//             if (device.id == id) {
//                 return &device;
//             }
//         }
//         return nullptr;
//     }
// };

// #endif // DEVICE_MODEL_H
