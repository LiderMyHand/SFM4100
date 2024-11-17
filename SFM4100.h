#ifndef SFM4100_H
#define SFM4100_H

#include <Arduino.h>
#include <Wire.h>

class SFM4100 {
public:
    // Constructor
    SFM4100(uint8_t address, uint8_t sdaPin, uint8_t sclPin);

    // Public methods
    void begin();
    void softReset();
    int16_t readFlow();
    
private:
    uint8_t _address;
    uint8_t _sdaPin;
    uint8_t _sclPin;

    uint8_t calculateCRC(uint8_t *data, uint8_t length);
};

#endif
