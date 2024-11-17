# SFM4100 Arduino Library

The **SFM4100 Arduino Library** provides an easy-to-use interface for the Sensirion SFM4100 digital mass flow sensor. This library supports I2C communication, data retrieval, and CRC-8 validation for reliable measurements.

## Features

- Supports communication with the SFM4100 mass flow sensor via I2C.
- Handles signed 16-bit measurements for both positive and negative flow.
- Performs CRC-8 validation to ensure data integrity.
- Includes examples for quick setup and usage.

## Installation

1. Download the library from the [GitHub repository](https://github.com/LiderMyHand/SFM4100).
2. Place the extracted `SFM4100` folder in your Arduino `libraries` directory:
   - On Windows: `Documents/Arduino/libraries`
   - On macOS: `~/Documents/Arduino/libraries`
   - On Linux: `~/Arduino/libraries`
3. Restart the Arduino IDE.
4. The library will now appear in the **Sketch > Include Library** menu.

Alternatively, you can use the Arduino Library Manager (once it is added) to install the library directly.

## Usage

### Basic Example

Below is a simple example to get started with the SFM4100 sensor:

```cpp
#include <SFM4100.h>

// Define sensor's I2C address and pins
#define SFM4100_ADDRESS 0x01
#define SDA_PIN 32
#define SCL_PIN 33

SFM4100 sensor(SFM4100_ADDRESS, SDA_PIN, SCL_PIN);

void setup() {
    Serial.begin(9600);
    sensor.begin();

    // Optional: Perform a soft reset
    sensor.softReset();
    delay(500); // Allow the sensor to reset
}

void loop() {
    int16_t flow = sensor.readFlow();

    if (!isnan(flow)) {
        Serial.print("Flow (SCCM): ");
        Serial.print(flow);
        //Serial.print("Flow (SLPM): "); // divide by 1000 to get SLPM
        //Serial.println(flow/1000.0);
        //
    } else {
        Serial.println("CRC or communication error");
    }

    delay(100); // Wait before taking another measurement
}
