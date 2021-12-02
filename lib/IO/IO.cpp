#include <Arduino.h>
#include "constants.h"
#include "IO.h"

IO *IO::instance = 0;

IO *IO::getInstance()
{
  if (instance == 0)
  {
    instance = new IO();
  }
  return instance;
}

bool IO::isInit(uint8_t pin)
{
  bool checkOut = std::find(outputPins.begin(), outputPins.end(), pin) != outputPins.end();
  bool checkIn = std::find(inputPins.begin(), inputPins.end(), pin) != inputPins.end();
  return checkOut || checkIn;
}

bool IO::gpioStatus(uint8_t pin)
{
  int key = std::find(outputPins.begin(), outputPins.end(), pin) != outputPins.end();
  Serial.println(key);
  return true;
}