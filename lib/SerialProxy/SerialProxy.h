#ifndef SERIAL_PROXY_H
#define SERIAL_PROXY_H

#include <Mqtt.h>

class SerialProxy
{
private:
  static SerialProxy *instance;

public:
  static SerialProxy *getInstance();
  SerialProxy();

  void init();
  void loop();
};

#endif