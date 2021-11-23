#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <WiFiManager.h>
#include <Api.h>
#include <constants.h>
Api api;

void setup()
{
  EEPROM.begin(256);
  Serial.begin(9600);

  WiFiManager wifi;
  wifi.info();
  api.init();
  //Serial.printf(" ESP8266 Chip id = %08X\n", ESP.getChipId());
}

void loop()
{
  api.handleClient();
  if (WiFi.status() != WL_CONNECTED)
  {
    ESP.restart();
  }
}