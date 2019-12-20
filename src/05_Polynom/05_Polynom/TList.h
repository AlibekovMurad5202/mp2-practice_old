#ifndef __TLIST_H__
#define __TLIST_H__
#include "MyExceptions.h"
//#include "TNode.h"
#include "Monom.h"

//~~~~~~~~~~~~~~~~~~~~~~~~ class TList ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template <typename TKey, typename TData>
class TList
{
protected:
  TNode<TKey, TData>* pFirst;
  TNode<TKey, TData>* pNext;
  TNode<TKey, TData>* pPrevious;
  TNode<TKey, TData>* pCurrent;

public:
  TList();
  TList(const TList<TKey, TData>& _tlist);
  TList(const TNode<TKey, TData>* _tnode);
  ~TList();

  void InsertBegin(TKey _newKey, TData _data);
  void InsertEnd(TKey _newKey, TData _data);
  void InsertBefore(TKey _key, TKey _newKey, TData _data);
  void InsertAfter(TKey _key, TKey _newKey, TData _data);

  void InsertBegin(const TNode<TKey, TData>& _tnode);
  void InsertEnd(const TNode<TKey, TData>& _tnode);
  void InsertBefore(TKey _key, const TNode<TKey, TData>& _tnode);
  void InsertAfter(TKey _key, const TNode<TKey, TData>& _tnode);

  void Remove(TKey _key);

  void Reset();
  void Next();

  bool IsEnded() const;
  bool IsEmpty() const;

  TKey getCurrentNodeKey() const;
  TData getCurrentNodeData() const;

  template <typename TKey, typename TData>
  friend std::ostream& operator<<(std::ostream& out, const TList<TKey, TData>& _tlist);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template <typename TKey, typename TData>
TList<TKey, TData>::TList()
{
  pFirst = nullptr;
  pPrevious = nullptr;
  pNext = nullptr;
  pCurrent = nullptr;
}

template <typename TKey, typename TData>
TList<TKey, TData>::TList(const TList& _tlist)
{
  pFirst = new TNode<TKey, TData>(*(_tlist.pFirst));
  TNode<TKey, TData>* node = pFirst;
  TNode<TKey, TData>* tmp = _tlist.pFirst;
  if (tmp != nullptr)
  {
  while (tmp->pNext != nullptr)
  {
    node->pNext = new TNode<TKey, TData>(*(tmp->pNext));
    node = node->pNext;
    tmp = tmp->pNext;
  }
  pPrevious = nullptr;
  pCurrent = pFirst;
  if (pFirst->pNext != nullptr)
    pNext = pFirst->pNext;

  }
}

template <typename TKey, typename TData>
TList<TKey, TData>::TList(const TNode<TKey, TData> * _tnode)
{
  pFirst = new TNode<TKey, TData>(*_tnode);
  pCurrent = pFirst;
  pPrevious = nullptr;
  pNext = nullptr;
}

template <typename TKey, typename TData>
TList<TKey, TData>::~TList()
{
  TNode<TKey, TData> *del = pFirst;
  TNode<TKey, TData> *next;
  while (del != nullptr)
  {
    next = del->pNext;
    delete del;
    del = next;
  }
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertBegin(TKey _newKey, TData _data)
{
  if (pFirst == nullptr)
  {
    pFirst = new TNode<TKey, TData>(_newKey, _data);
    pCurrent = pFirst;
    return;
  }
  TNode<TKey, TData>* newFirstNode = new TNode<TKey, TData>(_newKey, _data);
  newFirstNode->pNext = pFirst;
  if (pCurrent == pFirst)
    pPrevious = newFirstNode;
  pFirst = newFirstNode;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertEnd(TKey _newKey, TData _data)
{
  if (pFirst == nullptr)
  {
    pFirst = new TNode<TKey, TData>(_newKey, _data);
    pCurrent = pFirst;
    return;
  }
  TNode<TKey, TData>* lastNode = new TNode<TKey, TData>(_newKey, _data);
  TNode<TKey, TData>* penultimateNode = pFirst;
  while (penultimateNode->pNext != nullptr)
  {
    penultimateNode = penultimateNode->pNext;
  }
  penultimateNode->pNext = lastNode;
  if (pCurrent = penultimateNode)
    pNext = lastNode;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertBefore(TKey _key, TKey _newKey, TData _data)
{
  if (pFirst == nullptr) return;
  if (pFirst->key == _key)
  {
    InsertBegin(_newKey, _data);
    return;
  }
  TNode<TKey, TData>* previousNode = pFirst;
  while ((previousNode->pNext != nullptr) && (previousNode->pNext->key != _key))
  {
    previousNode = previousNode->pNext;
  }
  if (previousNode->pNext == nullptr)
    throw ExceptionNoNodeInList(__LINE__, __FILE__);
  TNode<TKey, TData>* nextNode = previousNode->pNext;
  TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_newKey, _data);
  previousNode->pNext = newNode;
  newNode->pNext = nextNode;
  if (pCurrent == previousNode)
    pNext = newNode;
  if (pCurrent == nextNode)
    pPrevious = newNode;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertAfter(TKey _key, TKey _newKey, TData _data)
{
  if (pFirst == nullptr) return;
  TNode<TKey, TData>* previousNode = pFirst;
  while ((previousNode != nullptr) && (previousNode->key != _key))
  {
    previousNode = previousNode->pNext;
  }
  if (previousNode == nullptr)
    throw ExceptionNoNodeInList(__LINE__, __FILE__);
  TNode<TKey, TData>* nextNode = previousNode->pNext;
  TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_newKey, _data);
  previousNode->pNext = newNode;
  newNode->pNext = nextNode;
  if (pCurrent == previousNode)
    pNext = newNode;
  if (pCurrent == nextNode)
    pPrevious = newNode;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertBegin(const TNode<TKey, TData>& _tnode)
{
  InsertBegin(_tnode.key, _tnode.data);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertEnd(const TNode<TKey, TData>& _tnode)
{
  InsertEnd(_tnode.key, _tnode.data);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertBefore(TKey _key, const TNode<TKey, TData>& _tnode)
{
  InsertBefore(_key, _tnode.key, _tnode.data);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertAfter(TKey _key, const TNode<TKey, TData>& _tnode)
{
  InsertAfter(_key, _tnode.key, _tnode.data);
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Remove(TKey _key)
{
  if (pFirst == nullptr) return;
  if (pFirst->key == _key)
  {
    bool wasFirstNodeCurrent = (pCurrent == pFirst);
    bool wasFirstNodePrevious = (pPrevious == pFirst);
    TNode<TKey, TData>* nextNode = pFirst->pNext;
    delete pFirst;
    pFirst = nextNode;
    if (wasFirstNodeCurrent)  pCurrent = nullptr;
    if (wasFirstNodePrevious) pPrevious = nullptr;
    return;
  }
  TNode<TKey, TData>* previousNode = pFirst;
  while ((previousNode->pNext != nullptr) && (previousNode->pNext->key != _key))
  {
    previousNode = previousNode->pNext;
  }
  if (previousNode->pNext == nullptr)
    throw ExceptionNoNodeInList(__LINE__, __FILE__);
  TNode<TKey, TData>* nextNode = previousNode->pNext->pNext;
  bool wasRemovingNodeCurrent = (pCurrent == previousNode->pNext);
  bool wasRemovingNodeNext = (pNext == previousNode->pNext);
  delete previousNode->pNext;
  previousNode->pNext = nextNode;
  if (wasRemovingNodeCurrent)
    pCurrent = nullptr;
  if (wasRemovingNodeNext)
    pNext = nullptr;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Reset()
{
  pCurrent = pFirst;
  pPrevious = nullptr;
  if (pFirst != nullptr)
    pNext = pFirst->pNext;
}

template <typename TKey, typename TData>
bool TList<TKey, TData>::IsEnded() const
{
  if (pCurrent == nullptr)
    return true;
  return false;
}

template <typename TKey, typename TData>
bool TList<TKey, TData>::IsEmpty() const
{
  return (pFirst == nullptr);
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Next()
{
  if (IsEnded() == true) 
    throw ExceptionListIsEnded(__LINE__, __FILE__);
  pPrevious = pCurrent;
  pCurrent = pNext;
  if (pNext != nullptr)
  {
    pNext = pNext->pNext;
  }
}

template <typename TKey, typename TData>
TKey TList<TKey, TData>::getCurrentNodeKey() const
{
  if (pCurrent == nullptr)
  {
    throw ExceptionNoNodeInList(__LINE__, __FILE__);

  }
  return pCurrent->key;
}

template <typename TKey, typename TData>
TData TList<TKey, TData>::getCurrentNodeData() const
{
  if (pCurrent == nullptr)
  {
    throw ExceptionNoNodeInList(__LINE__, __FILE__);

  }
  return pCurrent->data;
}

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& out, const TList<TKey, TData>& _tlist)
{
  TNode<TKey, TData> *node = _tlist.pFirst;
  while (node != nullptr)
  {
    out << *(node);
    if (node->pNext != nullptr)
      out << " --> ";
    node = node->pNext;
  }
  return out;
};

#endif // !__TLIST_H__