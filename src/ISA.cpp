#include "ISA.h"

ISA::ISA(uint8_t address) : _address(address) {}

bool ISA::begin() {
    Wire.begin();
    return readSensor();
}

bool ISA::readSensor() {
    Wire.beginTransmission(_address);
    Wire.write(0x2C);
    Wire.write(0x06);
    if (Wire.endTransmission(false) != 0)
        return false;

    delay(500);  // Measurement duration

    Wire.requestFrom(_address, (uint8_t)6);

    uint16_t rawTemperature = (Wire.read() << 8) | Wire.read();
    Wire.read();
    uint16_t rawHumidity = (Wire.read() << 8) | Wire.read();
    Wire.read();

    // TODO: Add CRC check here

    _temperature = 175.0 * rawTemperature / 65535.0 - 45.0;
    _humidity = 100.0 * rawHumidity / 65535.0;

    return true;
}

bool ISA::getData(float &temp, float &humi) {
    readSensor();

    temp = _temperature;
    humi = _humidity;
    return true;  // Return true for successful read (add error handling if needed)
}

bool ISA::getJSON(JsonObject &doc) {
    readSensor();

    JsonArray dataArray = doc.createNestedArray("ISA");

    JsonObject dataSet = dataArray.createNestedObject();  // First data set
    dataSet["name"] = "Temperature";
    dataSet["value"] = _temperature;
    dataSet["unit"] = "ºC";

    dataSet = dataArray.createNestedObject();  // Subsequent data sets
    dataSet["name"] = "Humidity";
    dataSet["value"] = _humidity;
    dataSet["unit"] = "%RH";

    return true;
}