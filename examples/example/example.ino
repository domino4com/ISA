#include <ArduinoJson.h>
#ifndef I2S_WS
#define I2S_WS 43
#endif
#ifndef I2S_SCK
#define I2S_SCK 44
#endif
#ifndef I2S_SD
#define I2S_SD 1
#endif
#include "ISA.h"
ISA input;
double var1;
char s[] = "SPL: %.2f dBa\n";

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.printf("\nISA Example Test\n");

    if (input.begin()) {
        Serial.println("ISA initialized successfully.");
    } else {
        Serial.println("Failed to initialize ISA");
        exit(0);
    }
}

void loop() {
    if (input.getData(var1)) {
        Serial.printf(s, var1);
    } else {
        Serial.println("Failed to get ISA data.");
    }

    delay(1000);
}
