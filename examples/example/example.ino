#include <ArduinoJson.h>
#include <Wire.h>
#ifndef I2C_SDA
#define I2C_SDA SDA
#endif
#ifndef I2C_SCL
#define I2C_SCL SCL
#endif

#include "ISA.h"
ISA input;
float var1, var2;
char s[] = "Temperature: %.2f ºC, Humidity: %.2f %%RH\n";

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.printf("\nISA Example Test\n");

    Wire.setPins(I2C_SDA, I2C_SCL);
    Wire.begin();

    if (input.begin()) {
        Serial.println("ISA initialized successfully.");
    } else {
        Serial.println("Failed to initialize ISA");
        exit(0);
    }
}

void loop() {
    if (input.getData(var1, var2)) {
        Serial.printf(s, var1, var2);
    } else {
        Serial.println("Failed to get $$$ data.");
    }

    delay(1000);
}
