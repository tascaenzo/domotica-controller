#ifndef IO_H
#define IO_H

class IO
{
private:
  static IO *instance;

public:
  static IO *getInstance();
  bool isInit(uint8_t pin);
  IO();

  bool gpioGetStatus(uint8_t pin);
  bool gpioSetStatus(uint8_t pin, bool status);

};

#endif