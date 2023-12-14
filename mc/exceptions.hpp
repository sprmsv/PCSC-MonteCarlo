#ifndef MC_EXCEPTIONS_HPP
#define MC_EXCEPTIONS_HPP

#include <string>

struct Exception {
  Exception(const std::string &mesg = "") : mesg(mesg){};
  const std::string &what() const {return mesg;};
private:
  std::string mesg;
};

struct ArgumentParseException : public Exception {
  ArgumentParseException(const std::string &argname, const std::string &mesg = "")
    : Exception(mesg), argname(argname) {};
  std::string argname;
};

struct ArgumentMissingException : public ArgumentParseException {
  ArgumentMissingException(const std::string &argname, const std::string &mesg = "")
    : ArgumentParseException(argname, mesg) {};
};

struct InvalidArgumentException : public ArgumentParseException {
  InvalidArgumentException(const std::string &argname, const std::string &mesg = "")
    : ArgumentParseException(argname, mesg) {};
};

struct FileNotFoundException : public ArgumentParseException {
  FileNotFoundException(const std::string &argname, const std::string &mesg = "")
    : ArgumentParseException(argname, mesg) {};
};

struct FunctionNotSupported : public Exception {
  FunctionNotSupported(const std::string &mesg = "")
    : Exception(mesg) {};
};

struct InvalidInputException : public Exception {
  InvalidInputException(const std::string &mesg = "")
    : Exception(mesg) {};
};


#endif
