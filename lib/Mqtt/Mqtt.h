#ifndef MQTT_H
#define MQTT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class Mqtt
{
private:
  //singleton instance
  static Mqtt *instance;

  WiFiClient espClient;
  PubSubClient mqttClient;

public:
  static Mqtt *getInstance();
  Mqtt();

  void init();
  void loop();

  void sendMessage(String payload);
  
  static void callback(char* topic, byte* payload, unsigned int length);
};

#endif