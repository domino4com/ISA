#include <ArduinoJson.h>
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
