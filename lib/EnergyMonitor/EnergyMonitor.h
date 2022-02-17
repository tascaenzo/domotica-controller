#ifndef ENERGY_MONITOR_H
#define ENERGY_MONITOR_H

class EnergyMonitor{
  private:
  static EnergyMonitor *instance;

  public:
  static EnergyMonitor *getInstance();
  EnergyMonitor();

  void init();
  void loop();
};

#endif