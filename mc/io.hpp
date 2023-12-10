#ifndef MC_IO_HPP
#define MC_IO_HPP

#include "functions.hpp"
#include <string>

// TODO: Make this an abstract class
class Reader {
public:
  Reader(std::string filepath);
  virtual void parser() = 0;
private:
  std::string filepath;
};

class ReaderTxt: public Reader{
public:
  ReaderTxt(std::string filepath);
  virtual void parser();
};
#endif
