#ifndef CONTANTS_H
#define CONTANTS_H

#define API_URL "http://192.168.1.70:3000/iot-devices"
#define API_KEY "api_key"

#define SERVER_PORT 3000
#define ALLOW_ORIGIN "192.168.1.70"

#define DEVICE_ID String(ESP.getChipId()).c_str()

const std::vector<uint8_t> inputPins({D1, D2});
const std::vector<uint8_t> outputPins({LED_BUILTIN});

#endif