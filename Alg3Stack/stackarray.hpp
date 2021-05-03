#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP

#include <utility>
#include <cstddef>
#include "stack.hpp"
#include "errors.hpp"

template <typename T>
class StackArray: public Stack<T>
{
public:
  StackArray<T>(int stackSize)
  {
    if (stackSize > 0)
    {
      array_ = new T[stackSize + 1];
      top_ = stackSize;
      size_ = stackSize;
    }
    else
    {
      throw WrongSizeException();
    }
  }
  StackArray(const StackArray<T>& src) = delete;
  StackArray(StackArray<T>&& src)
  {
    array_ = nullptr;
    top_ = NULL;
    size_ = NULL;
    swap(&this, src);
  }
  StackArray<T>& operator=(const StackArray<T>& src) = delete;
  StackArray<T>& operator=(StackArray<T>&& src)
  {
    delete array_;
    array_ = nullptr;
    top_ = NULL;
    size_ = NULL;
    swap(&this, src);
  }
  virtual ~StackArray<T>()
  {
    delete [] array_;
  }
  void push(const T& elem)
  {
    if (this->isFull())
    {
     throw StackOverflow();
    }
    else
    {
      array_[top_] = elem;
      top_--;
    }
  }
  T pop()
  {
    if (this->isEmpty())
    {
     throw StackUnderflow();
    }
    else
    {
     top_++;
     return array_[top_];
    }
  }
  bool isEmpty()
  {
    if (top_ == size_)
    {
     return true;
    }
    else
    {
     return false;
    }
  }
  bool isFull()
  {
   if (top_ == 0)
   {
     return true;
   }
   else
   {
     return false;
   }
  }
  T top()
  {
    return array_[top_ + 1];
  }

private:
  T * array_;
  size_t top_;
  size_t size_;
  friend void swap(StackArray<T>& stack1, StackArray<T>& stack2)
  {
    std::swap(stack1.array_, stack2.array_);
    std::swap(stack1.top_, stack2.top_);
    std::swap(stack1.size_, stack2.size_);
  }
};

#endif
