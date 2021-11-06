#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>


void setup()
{
  EEPROM.begin(128);
  Serial.begin(9600);

  WiFiManager wifi;
  wifi.info();
  
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    ESP.restart();
  }
}