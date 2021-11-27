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