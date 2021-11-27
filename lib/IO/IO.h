#ifndef IO_H
#define IO_H

class IO{
  private:
  //singleton instance
  static IO *instance;

  public:
  static IO *getInstance();
};

#endif