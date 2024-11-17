#include "SFM4100.h"

// Command bytes
#define SFM4100_TRIGGER_MEASUREMENT 0xF1
#define SFM4100_SOFT_RESET 0xFE

SFM4100::SFM4100(uint8_t address, uint8_t sdaPin, uint8_t sclPin) 
    : _address(address), _sdaPin(sdaPin), _sclPin(sclPin) {}

void SFM4100::begin() {
    Wire.begin(_sdaPin, _sclPin);
}

void SFM4100::softReset() {
    Wire.beginTransmission(_address);
    Wire.write(SFM4100_SOFT_RESET);
    Wire.endTransmission();
}

int16_t SFM4100::readFlow() {
    Wire.beginTransmission(_address);
    Wire.write(SFM4100_TRIGGER_MEASUREMENT); // Send trigger command
    Wire.endTransmission();

    delay(10); // Short delay to allow measurement to complete

    Wire.requestFrom(_address, (uint8_t)3); // Request 2 bytes + 1 CRC byte

    if (Wire.available() == 3) {
        byte msb = Wire.read();  // Most Significant Byte
        byte lsb = Wire.read();  // Least Significant Byte
        byte crc = Wire.read();  // CRC byte

        int16_t rawFlow = (msb << 8) | lsb;

        // Validate CRC-8
        uint8_t data[] = {msb, lsb};
        if (calculateCRC(data, 2) == crc) {
            return rawFlow; // Return flow in SCCM
        } else {
            return NAN; // Return NaN for CRC failure
        }
    }
    return NAN; // Return NaN for communication error
}

uint8_t SFM4100::calculateCRC(uint8_t *data, uint8_t length) {
    uint8_t crc = 0x00; // Initial value
    uint8_t polynomial = 0x31; // CRC polynomial (x^8 + x^5 + x^4 + 1)

    for (uint8_t i = 0; i < length; i++) {
        crc ^= data[i]; // XOR-in the next byte

        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ polynomial; // Apply polynomial if MSB is set
            } else {
                crc <<= 1; // Shift left
            }
        }
    }

    return crc;
}
