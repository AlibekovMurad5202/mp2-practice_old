#ifndef __TNODE_H__
#define __TNODE_H__
#include "iostream"

//~~~~~~~~~~~~~~~~~~~~~~~~ struct TNode ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template <typename TKey, typename TData>
struct TNode
{
  TKey key;
  TData data;
  TNode* pNext;

  TNode();
  TNode(TKey _key, TData _data);
  TNode(const TNode<TKey, TData>& _tnode);
  ~TNode();

  const TNode<TKey, TData>& operator=(const TNode<TKey, TData>& _tnode);

  template <typename TKey, typename TData>
  friend std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>& _tnode);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode()
{
  key = 0;
  pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(TKey _key, TData _data)
{
  pNext = nullptr;
  key = _key;
  data = _data;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& _tnode)
{
  data = _tnode.data;
  pNext = nullptr;
  key = _tnode.key;
}

template<typename TKey, typename TData>
TNode<TKey, TData>::~TNode()
{
  pNext = nullptr;
}

template<typename TKey, typename TData>
const TNode<TKey, TData>& TNode<TKey, TData>::operator=(const TNode<TKey, TData>& _tnode)
{
  if (this != &_tnode)
  {
    key = _tnode.key;
    data = _tnode.data;
  }
  return *this;  
}

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>& node)
{
  out << "[" << node.key << " : " << node.data << "]";
  return out;
};

#endif // !__TNODE_H__