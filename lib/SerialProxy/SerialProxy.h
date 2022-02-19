#ifndef ENERGY_MONITOR_H
#define ENERGY_MONITOR_H

#include <Mqtt.h>

class SerialProxy{
  private:
  static SerialProxy *instance;

  public:
  static SerialProxy *getInstance();
  SerialProxy();

  void init();
  void loop();
};

#endif