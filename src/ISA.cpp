#include "ISA.h"

// I2S configuration for reading from microphone
const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,  // Higher sample rate for better filter performance
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,  // I2S_COMM_FORMAT_STAND_MSB, //I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0};



// Simplified A-weighting filter coefficients
// Note: These are approximate and designed for 44.1kHz. Adjust coefficients if using a different sample rate.
const float a_weighting_filter_coeffs[3] = {0.255978, 0.488037, 0.255978};

ISA::ISA() {

}

bool ISA::begin(uint8_t ws, uint8_t sck, uint8_t sd) {
// I2S pin configuration
const i2s_pin_config_t pin_config = {
    .bck_io_num = sck,
    .ws_io_num = ws,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = sd};

    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);
    return true;
}

bool ISA::readSensor() {
    // Buffer to read data into and apply A-weighting
    int32_t buffer[64];
    static float filtered_samples[64] = {0};

    // Read data from the I2S peripheral
    size_t bytes_read;
    i2s_read(I2S_NUM_0, &buffer, sizeof(buffer), &bytes_read, portMAX_DELAY);

    // Apply simplified A-weighting filter (FIR filter)
    for (int i = 2; i < bytes_read / sizeof(int32_t); i++) {
        filtered_samples[i] = a_weighting_filter_coeffs[0] * buffer[i - 2] + a_weighting_filter_coeffs[1] * buffer[i - 1] + a_weighting_filter_coeffs[2] * buffer[i];
    }

    // Calculate RMS of the filtered buffer
    double rms = 0;
    for (int i = 0; i < bytes_read / sizeof(int32_t); i++) {
        rms += pow(filtered_samples[i] / (double)(INT32_MAX), 2);
    }
    rms = sqrt(rms / (bytes_read / sizeof(int32_t)));

    // Calculate SPL in dBA
    _spl = 20 * log10(rms);

    return true;
}

bool ISA::getData(double &spl) {
    readSensor();
    spl = _spl;
    return true;  // Return true for successful read (add error handling if needed)
}

bool ISA::getJSON(JsonObject &doc) {
    readSensor();

    JsonArray dataArray = doc.createNestedArray("ISA");

    JsonObject dataSet = dataArray.createNestedObject();  // First data set
    dataSet["name"] = "Sound Pressure Level";
    dataSet["value"] = _spl;
    dataSet["unit"] = "dBa";

    return true;
}