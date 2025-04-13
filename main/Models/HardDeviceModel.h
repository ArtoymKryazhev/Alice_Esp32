#ifndef HARD_DEVICE_MODEL_H
#define HARD_DEVICE_MODEL_H

#include "Models/PinModel/BasePinModel.h"
#include <vector>

class HardDeviceModel {
public:
    virtual ~HardDeviceModel() {}  // Виртуальный деструктор для корректного удаления объектов

    virtual std::vector<const BasePinModel*> getAllPin() const = 0;

};

#endif // HARD_DEVICE_MODEL_H