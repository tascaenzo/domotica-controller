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

IO::IO()
{
  for (auto pin : inputPins)
  {
    pinMode(pin, INPUT_PULLUP);
  }

  for (auto pin : outputPins)
  {
    pinMode(pin, OUTPUT);
  }
}

bool IO::isInit(uint8_t pin)
{
  bool checkOut = std::find(outputPins.begin(), outputPins.end(), pin) != outputPins.end();
  bool checkIn = std::find(inputPins.begin(), inputPins.end(), pin) != inputPins.end();
  return checkOut || checkIn;
}

bool IO::gpioGetStatus(uint8_t pin)
{
  return digitalRead(pin);
}

bool IO::gpioSetStatus(uint8_t pin, bool status)
{
  digitalWrite(pin, status);
  return this->gpioGetStatus(pin);
}
