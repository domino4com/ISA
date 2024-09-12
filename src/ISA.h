#ifndef ISA_H
#define ISA_H

#include <ArduinoJson.h>
#include "Arduino.h"
#include <driver/i2s.h>
#include <cmath>

class ISA {
   public:
    ISA();
    bool begin(uint8_t ws = 43, uint8_t sck = 44, uint8_t sd = 1);
    bool getData(double &spl);
    bool getJSON(JsonObject &doc);

   private:
    double _spl;
    bool readSensor();
};

#endif  // ISA_H