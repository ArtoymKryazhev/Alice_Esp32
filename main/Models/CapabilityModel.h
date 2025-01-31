#include "HardwareSerial.h"
#ifndef CAPABILITYMODEL_H
#define CAPABILITYMODEL_H

#include <ArduinoJson.h>
#include <optional>
#include "C:/Dev/Edu/Arduino/Alice_Esp32/main/Enums/CapabilityTypeEnum.h"
#include "StateModel.h"

class CapabilityModel {
private:
    CapabilityTypeEnum type;                // Тип Capability
    std::optional<StateModel> state;        // Необязательное состояние

public:
    // Конструктор
    CapabilityModel(CapabilityTypeEnum type, std::optional<StateModel> state = std::nullopt)
        : type(type), state(state) {}

    // Получить тип
    CapabilityTypeEnum getType() const {
        return type;
    }

    // Установить статус действия
    void setActionStatus(String instance, ActionResultModel actionResult) {
        if (!state.has_value()) {
            state = StateModel(instance);  // Создаем новое состояние, если его нет
        }
        state->setActionResult(actionResult);
    }

    // Сериализация в JSON
    void serializeToJson(JsonDocument& doc) const {
        doc["type"] = capabilityTypeToString(type);
        if (state.has_value()) {
            JsonDocument stateDoc;  // Создаем временный документ для сериализации состояния
            state->serializeToJson(stateDoc);  // Сериализуем состояние в stateDoc
            doc["state"] = stateDoc.as<JsonObject>();  // Добавляем сериализованный объект состояния
        }
    }


  static CapabilityModel from(const JsonObject& data) {

    CapabilityTypeEnum type = CapabilityTypeEnum::UNKNOWN;
    std::optional<StateModel> state = std::nullopt;

    // Создаём модель типа CapabilityTypeEnum
        

    if (!data["type"].isNull()) {
        type = fromCapabilityTypeEnum(data);
    } 

    // Проверяем наличие состояния и если оно есть, создаём объект StateModel
    if (!data["state"].isNull()) {
        state = StateModel::from(data["state"]);
    }

      return CapabilityModel(type, state);
  }

    // Статический метод для создания объектов из массива и сохранения в JsonArray
    static JsonArray fromBatch(const JsonArray& capabilities, JsonArray& JsonArrayCapabilities) {
      for (JsonObject capability : capabilities) {
          // Пробуем создать CapabilityModel      
          if (fromCapabilityTypeEnum(capability) != CapabilityTypeEnum::UNKNOWN) {
              CapabilityModel capabilityModelOpt = CapabilityModel::from(capability);
              JsonDocument doc;
              capabilityModelOpt.serializeToJson(doc);        
              JsonArrayCapabilities.add(doc);   
          } else {
              Serial.println("Skipping invalid capability.");
              continue;
          }
      }

      return JsonArrayCapabilities;     
    }
};

#endif // CAPABILITYMODEL_H
