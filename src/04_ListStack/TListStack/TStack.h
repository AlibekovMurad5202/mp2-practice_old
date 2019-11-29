#ifndef __STACK_H__
#define __STACK_H__

#include "MyExceptions.h"

template<typename ValueType>
class TStack
{
public:
  virtual void Push(ValueType element) = 0;
  virtual ValueType Top() const = 0;
  virtual void Pop() = 0;

  virtual bool IsEmpty()const = 0;
  virtual bool IsFull() const = 0;
};

#endif // !__STACK_H__