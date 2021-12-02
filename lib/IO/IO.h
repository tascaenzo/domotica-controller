#ifndef IO_H
#define IO_H

//enum GpioStaut {DIGITAL_IN, DIGITAL_OUT, ANALOGIC_IN}

class IO
{
private:
  static IO *instance;

public:
  static IO *getInstance();
  bool isInit(uint8_t pin);
  //IO();

  bool gpioStatus(uint8_t pin);
};

#endif