#ifndef __STACK__H__
#define __STACK__H__

#include "MyExceptions.h"

template<typename ValType>
class Stack
{
protected:
  int size;
  int head;
  ValType* elems;

public:
  explicit Stack(int _size = 5);
  Stack(const Stack<ValType>& _stack);
  ~Stack();

  void Push(ValType element);
  ValType Top() const;
  ValType Pop();

  bool IsEmpty() const;
  bool IsFull() const;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template<typename ValType>
Stack<ValType>::Stack(int _size)
  : size(_size), head(0)
{
  if (size <= 0)
  {
    ExceptionNotPositiveSize e(__LINE__, __FILE__);
    throw e;
  }
  elems = new ValType[size];
}

template<typename ValType>
Stack<ValType>::Stack(const Stack<ValType>& _stack)
  : size(_stack.size), head(_stack.head)
{
  elems = new ValType[size];
  for (int i = 0; i < head; i++)
    elems[i] = _stack.elems[i];
}

template<typename ValType>
Stack<ValType>::~Stack()
{
  delete[] elems;
}

template<typename ValType>
void Stack<ValType>::Push(ValType element)
{
  if (IsFull())
  {
    ExceptionFullStack e(__LINE__, __FILE__);
    throw e;
  }
  elems[head++] = element;
}

template<typename ValType>
ValType Stack<ValType>::Top() const
{
  if (IsEmpty())
  {
    ExceptionEmptyStack e(__LINE__, __FILE__);
    throw e;
  }
  return elems[head - 1];
}

template<typename ValType>
ValType Stack<ValType>::Pop()
{
  if (IsEmpty())
  {
    ExceptionEmptyStack e(__LINE__, __FILE__);
    throw e;
  }
  return elems[--head];
}

template<typename ValType>
bool Stack<ValType>::IsEmpty() const
{
  return (head == 0);
}

template<typename ValType>
bool Stack<ValType>::IsFull() const
{
  return (head == size);
};

#endif // !__STACK__H__