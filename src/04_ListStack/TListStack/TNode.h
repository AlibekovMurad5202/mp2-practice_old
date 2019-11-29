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
  pData = new TData;
  pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(TKey _key, TData* _data)
{
  pData = new TData;
  pNext = nullptr;
  key = _key;
  *pData = *_data;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& _tnode)
{
  pData = new TData;
  pNext = nullptr;
  key = _tnode.key;
  *pData = *_tnode.pData;
}

template<typename TKey, typename TData>
TNode<TKey, TData>::~TNode()
{
  if (pData)
    delete pData;
}

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>& node)
{
  out << "[" << node.key << " : " << *(node.pData) << "]";
  return out;
};

#endif // !__TNODE_H__