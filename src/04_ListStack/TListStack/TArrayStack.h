#ifndef __TARRAYSTACK_H__
#define __TARRAYSTACK_H__

#include "TStack.h"

template<typename ValType>
class TArrayStack : public TStack<ValType>
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
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template<typename ValType>
TArrayStack<ValType>::TArrayStack(int _size)
  : size(_size), head(0)
{
  if (size <= 0) throw ExceptionNotPositiveSize(__LINE__, __FILE__);
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
  if (IsFull()) throw ExceptionFullStack(__LINE__, __FILE__);
  elems[head++] = element;
}

template<typename ValType>
ValType TArrayStack<ValType>::Top() const
{
  if (IsEmpty()) throw ExceptionEmptyStack(__LINE__, __FILE__);
  return elems[head - 1];
}

template<typename ValType>
void TArrayStack<ValType>::Pop()
{
  if (IsEmpty()) throw ExceptionEmptyStack(__LINE__, __FILE__);
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
};

#endif // !__STACK_H__