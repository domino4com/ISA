#ifndef ISA_H
#define ISA_H

#include <ArduinoJson.h>

#include "Arduino.h"
#include "Wire.h"

#define SHT30_DIS_DEFAULT_ADDRESS 0x44

class ISA {
   public:
    ISA(uint8_t address = SHT30_DIS_DEFAULT_ADDRESS);
    bool begin();
    bool getData(float &temperature, float &humidity);
    bool getJSON(JsonObject &doc);

   private:
    uint8_t _address;
    float _temperature, _humidity;
    bool readSensor();
};

#endif  // ISA_H