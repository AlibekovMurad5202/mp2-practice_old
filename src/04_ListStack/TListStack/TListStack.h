#ifndef __TLISTSTACK_H__
#define __TLISTSTACK_H__


#include "Stack.h"
#include "TList.h"

// list:   [0 : ...] --> [0 : ...] --> [0 : ...] --> ... --> [0 : ...]
// stack: [   top           ...           ...        ...        ...   ]

template<typename ValType>
class TListStack : public Stack<ValType>
{
protected:
  TList<int, ValType>* list;

public:
  TListStack();
  TListStack(const TListStack& _stack);
  ~TListStack();

  void Push(ValType element);
  ValType Top() const;
  void Pop();

  bool IsEmpty() const;
  bool IsFull() const;
};

template<typename ValType>
TListStack<ValType>::TListStack()
{
  list = new TList<int, ValType>;
}

template<typename ValType>
TListStack<ValType>::TListStack(const TListStack& _stack)
{
  list = new TList<int, ValType>(*(_stack->list));
}

template<typename ValType>
TListStack<ValType>::~TListStack()
{
  delete list;
}

template<typename ValType>
void TListStack<ValType>::Push(ValType element)
{
  list->InsertBegin(0, &element);
}

template<typename ValType>
ValType TListStack<ValType>::Top() const
{
  if (IsEmpty())
  {
    ExceptionEmptyStack e(__LINE__, __FILE__);
    throw e;
  }
  return list->getFirstNodeData();
}

template<typename ValType>
void TListStack<ValType>::Pop()
{
  if (IsEmpty())
  {
    ExceptionEmptyStack e(__LINE__, __FILE__);
    throw e;
  }
  list->Remove(0);
}

template<typename ValType>
bool TListStack<ValType>::IsEmpty() const
{
  return list->IsEmpty();
}

template<typename ValType>
bool TListStack<ValType>::IsFull() const
{
  return false;
};

#endif // !__TLISTSTACK_H__