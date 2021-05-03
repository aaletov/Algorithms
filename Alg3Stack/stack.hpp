#ifndef STACK_HPP
#define STACK_HPP

template <typename T>
class Stack
{
public:
  virtual ~Stack() = default;
  virtual void push(const T& elem) = 0;
  virtual T pop() = 0;
  virtual bool isEmpty() = 0;
};

#endif
