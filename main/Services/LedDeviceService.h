#ifndef LED_DEVICE_SERVICE_H
#define LED_DEVICE_SERVICE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Models/LedDeviceModel.h"
#include "Models/ActionResultModel.h"
#include "Enums/ErrorCodeEnum.h"
#include "Services/PinService.h"

class LedDeviceService {
public:
    static ActionResultModel handle(LedDeviceModel* ledDevice, const JsonArray& capabilities) {
        for (JsonObject capability : capabilities) {
            const char* type = capability["type"];

            // Проверяем, что это нужная способность (on_off)
            if (strcmp(type, "devices.capabilities.on_off") == 0) {

                // Проверка наличия объекта state
                if (!capability["state"].is<JsonObject>()) {
                    return ActionResultModel(
                        ActionResultStatusEnum::ERROR,
                        ErrorCodeEnum::INVALID_VALUE,
                        "Отсутствует объект 'state'"
                    );
                }

                // Проверка, что внутри state есть логическое поле value
                if (!capability["state"]["value"].is<bool>()) {
                    return ActionResultModel(
                        ActionResultStatusEnum::ERROR,
                        ErrorCodeEnum::INVALID_VALUE,
                        "Параметр 'state.value' должен быть логического типа (true/false)"
                    );
                }

                // Получаем значение и включаем/выключаем свет
                bool value = capability["state"]["value"];
                if (value) {
                    ledDevice->turnOn();
                } else {
                    ledDevice->turnOff();
                }

                // Всё успешно
                return ActionResultModel(ActionResultStatusEnum::DONE);
            }
        }

        // Если нужной capability не нашли
        return ActionResultModel(
            ActionResultStatusEnum::ERROR,
            ErrorCodeEnum::INVALID_ACTION,
            "Не найдена поддерживаемая способность 'on_off'"
        );
    }

    static ActionResultModel stateDevice(LedDeviceModel* ledDevice, const CapabilityTypeEnum type) {
        if 
    }
};

#endif // LED_DEVICE_SERVICE_H
