#ifndef ACTION_RESULT_MODEL_H
#define ACTION_RESULT_MODEL_H

#include <ArduinoJson.h>
#include <optional>
#include "C:/Dev/Edu/Arduino/Alice_Esp32/main/Enums/ActionResultStatusEnum.h"
#include "C:/Dev/Edu/Arduino/Alice_Esp32/main/Enums/ErrorCodeEnum.h"

class ActionResultModel {
private:
    ActionResultStatusEnum status;                    // Обязательное поле
    std::optional<ErrorCodeEnum> errorCode;           // Необязательное поле
    std::optional<String> errorMessage;               // Необязательное поле

public:
    // Конструктор: статус, errorCode и errorMessage (все параметры)
    ActionResultModel(ActionResultStatusEnum status, 
                      std::optional<ErrorCodeEnum> errorCode = std::nullopt, 
                      std::optional<String> errorMessage = std::nullopt)
        : status(status), errorCode(errorCode), errorMessage(errorMessage) {}

    // Метод для сериализации в JSON
    void serializeToJson(JsonDocument& doc) const {
        // Сериализуем статус
        doc["status"] = actionResultStatusToString(status);

        // Если errorCode задан, добавляем его в JSON
        if (errorCode.has_value()) {
            doc["error_code"] = errorCodeToString(errorCode.value());
        }

        // Если есть сообщение об ошибке, добавляем его в JSON
        if (errorMessage.has_value() && !errorMessage.value().isEmpty()) {
            doc["error_message"] = errorMessage.value();
        }
    }
};

#endif // ACTION_RESULT_MODEL_H
