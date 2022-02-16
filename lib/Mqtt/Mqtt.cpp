#include "Mqtt.h"
#include "constants.h"

Mqtt *Mqtt::instance = 0;

Mqtt *Mqtt::getInstance()
{
  if (instance == 0)
  {
    instance = new Mqtt();
  }
  return instance;
}

void Mqtt::callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
}

Mqtt::Mqtt()
{
  mqttClient = PubSubClient(this->espClient);
  mqttClient.setServer(MQTT_BROKER_HOST, MQTT_BROKER_PORT);
  mqttClient.setCallback(Mqtt::callback);
}

void Mqtt::init()
{
  while (!mqttClient.connected())
  {
    String client_id = String(WiFi.macAddress());
    mqttClient.connect(client_id.c_str());

    delay(500);
    Serial.print(".");
  }
  mqttClient.subscribe(MQTT_DEVICE_TOPIC);
}

void Mqtt::loop(){
  this->mqttClient.loop();
}