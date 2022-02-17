#include "EneryMonitor.h"

EnergyMonitor *EnergyMonitor::instance = 0;

EnergyMonitor *EnergyMonitor::getInstance()
{
  if (instance == 0)
  {
    instance = new EnergyMonitor();
  }
  return instance;
}

  EnergyMonitor::EnergyMonitor(){

  }

  void EnergyMonitor::init(){

  }

  void EnergyMonitor::loop(){

  }