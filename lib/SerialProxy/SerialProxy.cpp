#include "SerialProxy.h"
#include <Mqtt.h>

SerialProxy *SerialProxy::instance = 0;

SerialProxy *SerialProxy::getInstance()
{
  if (instance == 0)
  {
    instance = new SerialProxy();
  }
  return instance;
}

SerialProxy::SerialProxy()
{
}

void SerialProxy::init()
{
  Serial.println("SerialProxy init");
}

void SerialProxy::loop()
{
  Mqtt *mqtt = Mqtt::getInstance();
  delay(250);
  mqtt->sendMessage("SerialProxy");
}