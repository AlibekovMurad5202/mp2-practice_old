#ifndef __TNODE_H__
#define __TNODE_H__
#include "iostream"

//~~~~~~~~~~~~~~~~~~~~~~~~ struct TNode ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template <typename TKey, typename TData>
struct TNode
{
  TKey key;
  TData* pData;
  TNode* pNext;

  TNode();
  TNode(TKey _key, TData* _data);
  TNode(const TNode<TKey, TData>& _tnode);
  ~TNode();

  template <typename TKey, typename TData>
  friend std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>& _tnode);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode()
{
  pData = nullptr;
  pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(TKey _key, TData* _data)
{
  pNext = nullptr;
  key = _key;
  if (_data != nullptr)
  {
    pData = new TData;
    *pData = *_data;
  }
  else pData = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& _tnode)
{
  if (_tnode.pData != nullptr)
  {
    pData = new TData;
    *pData = *_tnode.pData;
  }
  else pData = nullptr;
  pNext = nullptr;
  key = _tnode.key;
}

template<typename TKey, typename TData>
TNode<TKey, TData>::~TNode()
{
  if (pData != nullptr)
    delete pData;
}

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>& node)
{
  out << "[" << node.key << " : " << *(node.pData) << "]";
  return out;
};

#endif // !__TNODE_H__