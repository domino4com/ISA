#ifndef ISA_H
#define ISA_H

#include <ArduinoJson.h>
#include "Arduino.h"
#include <driver/i2s.h>
#include <cmath>

class ISA {
   public:
    ISA();
    bool begin();
    bool getData(double &spl);
    bool getJSON(JsonObject &doc);

   private:
    double _spl;
    bool readSensor();
};

#endif  // ISA_H