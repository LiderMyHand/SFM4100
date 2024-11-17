#include// <SFM4100.h>

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
    delay(500); // Allow some time for the sensor to reset
}

void loop() {
    double flow = sensor.readFlow();

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
