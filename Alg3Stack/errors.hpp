#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <exception>
#include <string>

class WrongSizeException: public std::exception
{
public:
  WrongSizeException():
    error_("Wrong size of stack") {};
  std::string getError() { return error_; };
private:
  std::string error_;
};

class StackUnderflow: public std::exception
{
public:
  StackUnderflow():
    error_("Stack is empty") {};
  std::string getError() { return error_; };
private:
  std::string error_;
};

class StackOverflow: public std::exception
{
public:
  StackOverflow():
    error_("Stack is full") {};
  std::string getError() { return error_; };
private:
  std::string error_;
};

#endif
