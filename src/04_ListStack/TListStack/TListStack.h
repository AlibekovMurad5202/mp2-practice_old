#ifndef __TLISTSTACK_H__
#define __TLISTSTACK_H__

#include "TStack.h"
#include "TList.h"

// list:   [0 : ...] --> [0 : ...] --> [0 : ...] --> ... --> [0 : ...]
// stack:  [  top           ...           ...        ...        ...  ]

template<typename ValType>
class TListStack : public TStack<ValType>
{
protected:
  TList<ValType, void*>* list;

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
  list = new TList<ValType, void*>;
}

template<typename ValType>
TListStack<ValType>::TListStack(const TListStack& _stack)
{
  list = new TList<ValType, void*>(*(_stack->list));
}

template<typename ValType>
TListStack<ValType>::~TListStack()
{
  delete list;
}

template<typename ValType>
void TListStack<ValType>::Push(ValType element)
{
  list->InsertBegin(element, nullptr);
}

template<typename ValType>
ValType TListStack<ValType>::Top() const
{
  if (IsEmpty()) throw ExceptionEmptyStack(__LINE__, __FILE__);
  return list->getFirstNodeKey();
}

template<typename ValType>
void TListStack<ValType>::Pop()
{
  if (IsEmpty()) throw ExceptionEmptyStack(__LINE__, __FILE__);
  list->Remove(list->getFirstNodeKey());
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