#ifndef __TARRAYSTACK_H__
#define __TARRAYSTACK_H__

#include "Stack.h"

template<typename ValType>
class TArrayStack : public Stack<ValType>
{
protected:
  int size;
  int head;
  ValType* elems;

public:
  explicit TArrayStack(int _size = 5);
  TArrayStack(const TArrayStack<ValType>& _stack);
  ~TArrayStack();

  void Push(ValType element);
  ValType Top() const;
  void Pop();

  bool IsEmpty() const;
  bool IsFull() const;

  //Stack<ValType>& operator=(const Stack<ValType>& _tstack);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template<typename ValType>
TArrayStack<ValType>::TArrayStack(int _size)
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
TArrayStack<ValType>::TArrayStack(const TArrayStack<ValType>& _stack)
  : size(_stack.size), head(_stack.head)
{
  elems = new ValType[size];
  for (int i = 0; i < head; i++)
    elems[i] = _stack.elems[i];
}

template<typename ValType>
TArrayStack<ValType>::~TArrayStack()
{
  delete[] elems;
}

template<typename ValType>
void TArrayStack<ValType>::Push(ValType element)
{
  if (IsFull())
  {
    ExceptionFullStack e(__LINE__, __FILE__);
    throw e;
  }
  elems[head++] = element;
}

template<typename ValType>
ValType TArrayStack<ValType>::Top() const
{
  if (IsEmpty())
  {
    ExceptionEmptyStack e(__LINE__, __FILE__);
    throw e;
  }
  return elems[head - 1];
}

template<typename ValType>
void TArrayStack<ValType>::Pop()
{
  if (IsEmpty())
  {
    ExceptionEmptyStack e(__LINE__, __FILE__);
    throw e;
  }
  --head;
}

template<typename ValType>
bool TArrayStack<ValType>::IsEmpty() const
{
  return (head == 0);
}

template<typename ValType>
bool TArrayStack<ValType>::IsFull() const
{
  return (head == size);
}

/*template<typename ValType>
Stack<ValType>& Stack<ValType>::operator=(const Stack<ValType>& _tstack)
{
  if (this == &_tstack)
    return *this;
  if (size != _tstack.size)
  {
    delete elems;
    size = _tstack.size;
    elems = new ValType[size];
  }
  head = _tstack.head;
  for (int i = 0; i < size; i++)
    elems[i] = _tstack.elems[i];
  return *this;
}*/;

#endif // !__STACK_H__