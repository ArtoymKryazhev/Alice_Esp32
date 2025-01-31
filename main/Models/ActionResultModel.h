#ifndef ACTION_RESULT_MODEL_H
#define ACTION_RESULT_MODEL_H

#include <ArduinoJson.h>
#include <optional>
#include "Enums/ActionResultStatusEnum.h"
#include "Enums/ErrorCodeEnum.h"

class ActionResultModel {
private:
    ActionResultStatusEnum status;                  // Обязательное поле - статус результата действия
    std::optional<ErrorCodeEnum> errorCode;         // Необязательное поле - код ошибки
    std::optional<String> errorMessage;             // Необязательное поле - сообщение об ошибке

public:
    // Конструктор: статус, errorCode и errorMessage (все параметры)
    ActionResultModel(ActionResultStatusEnum status, 
                      std::optional<ErrorCodeEnum> errorCode = std::nullopt, 
                      std::optional<String> errorMessage = std::nullopt)
        : status(status), errorCode(errorCode), errorMessage(errorMessage) {}

    // Метод для сериализации в JSON
    void serializeToJson(JsonDocument& doc) const {
        // Сериализуем статус в строковый формат
        doc["status"] = actionResultStatusToString(status);

        // Если errorCode задан, добавляем его в JSON
        if (errorCode.has_value()) {
            doc["error_code"] = errorCodeToString(errorCode.value());
        }

        // Если есть сообщение об ошибке и оно не пустое, добавляем его в JSON
        if (errorMessage.has_value() && !errorMessage.value().isEmpty()) {
            doc["error_message"] = errorMessage.value();
        }
    }
};

#endif // ACTION_RESULT_MODEL_H
