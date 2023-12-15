#ifndef MC_EXCEPTIONS_HPP
#define MC_EXCEPTIONS_HPP

#include <string>


/// @brief Base exception class for error handling.
struct Exception
{
  /// @brief Construct an exception with a message
  /// @param mesg The exception message.
  Exception(const std::string &mesg = "") : mesg(mesg){};
  /// @brief Return the exception message.
  const std::string &what() const {return mesg;};
private:
  /// @brief The exception message.
  std::string mesg;
};

/// @brief Exception for handling the errors in parsing the arguments.
struct ArgumentParseException : public Exception
{
  /// @brief construct an exception object.
  ArgumentParseException(const std::string &argname, const std::string &mesg = "")
    : Exception(mesg), argname(argname) {};
  std::string argname;
};

/// @brief Exception for handling the cases when an argument is expected but is not privided.
struct ArgumentMissingException : public ArgumentParseException
{
  /// @brief construct an exception object.
  ArgumentMissingException(const std::string &argname, const std::string &mesg = "")
    : ArgumentParseException(argname, mesg) {};
};

/// @brief Exception for handling the cases when an invalid argument is passed.
struct InvalidArgumentException : public ArgumentParseException
{
  /// @brief construct an exception object.
  InvalidArgumentException(const std::string &argname, const std::string &mesg = "")
    : ArgumentParseException(argname, mesg) {};
};

/// @brief Exception for handling the cases when a file or a directory cannot be found.
struct FileNotFoundException : public ArgumentParseException
{
  /// @brief construct an exception object.
  FileNotFoundException(const std::string &argname, const std::string &mesg = "")
    : ArgumentParseException(argname, mesg) {};
};

/// @brief Exception for handling the cases when a mathematical function is not supported.
struct FunctionNotSupported : public Exception
{
  /// @brief construct an exception object.
  FunctionNotSupported(const std::string &mesg = "")
    : Exception(mesg) {};
};

/// @brief Exception for handling the cases when a function or a method receives an invalid input.
struct InvalidInputException : public Exception
{
  /// @brief construct an exception object.
  InvalidInputException(const std::string &mesg = "")
    : Exception(mesg) {};
};

#endif
