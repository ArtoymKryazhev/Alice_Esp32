class PinOnOffInterface {
public:
    virtual void turnOn() = 0;  // Включить пин
    virtual void turnOff() = 0; // Выключить пин

    virtual ~PinOnOffInterface() = default; // Виртуальный деструктор на будущее
};
