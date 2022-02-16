#ifndef CONTANTS_H
#define CONTANTS_H

#define DEVICE_ID String(ESP.getChipId()).c_str()

// Mqtt constant
#define MQTT_BROKER_HOST "192.168.1.50"
#define MQTT_BROKER_PORT 1883
#define MQTT_BROKER_USERNAME ""
#define MQTT_BROKER_PASSWORD ""
#define MQTT_DEVICE_TOPIC "devices"

#endif