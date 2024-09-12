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

// Specifics
#include "ISA.h"
ISA input;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.printf("\nISA JSON Test\n");

    if (input.begin(I2S_WS, I2S_SCK, I2S_SD)) {
        Serial.println("ISA initialized successfully.");
    } else {
        Serial.println("Failed to initialize ISA!");
        exit(0);
    }
}

void loop() {
    StaticJsonDocument<256> doc;
    JsonObject root = doc.to<JsonObject>();

    if (input.getJSON(root)) {
        serializeJsonPretty(root, Serial);
        Serial.println();
    } else {
        Serial.println("Failed to get ISA data.");
    }

    delay(2000);
}
