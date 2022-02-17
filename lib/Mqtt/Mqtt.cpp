#include "Mqtt.h"
#include "constants.h"
#include <ArduinoJson.h>

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
  
  StaticJsonDocument<200> json;
  deserializeJson(json, payload);

  String action = json["action"].as<const char*>();

  if(action == "INFO"){
    Serial.printf("Info Controller");
  }

}

void Mqtt::sendMessage(String payload)
{
  String json;
  StaticJsonDocument<200> doc;

  doc["payload"] = payload;
  doc["devices"] = WiFi.macAddress();
  serializeJson(doc, json);

  this->mqttClient.publish(MQTT_DEVICE_TOPIC, json.c_str());
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

    delay(250);
    Serial.print(".");
  }
  mqttClient.subscribe(WiFi.macAddress().c_str());
}

void Mqtt::loop(){
  this->mqttClient.loop();
}
