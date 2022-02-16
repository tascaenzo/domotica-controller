#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <WiFiManager.h>
#include <IO.h>
#include <Mqtt.h>

#include <constants.h>

IO *io = IO::getInstance();
Mqtt* mqtt = Mqtt::getInstance();

void setup()
{
  EEPROM.begin(256);
  Serial.begin(9600);

  WiFiManager wifi;
  wifi.info();

  Serial.print("Mqtt init");
  mqtt->init();

  //Serial.printf("ESP8266 Chip id = %08X\n", ESP.getChipId());
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    ESP.restart();
  }
  mqtt->loop();
}