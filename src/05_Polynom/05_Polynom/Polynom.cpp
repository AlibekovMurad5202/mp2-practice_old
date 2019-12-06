#include "Polynom.h"

Polynom::Polynom()
{
  monoms = new TList<UINT, double>;
  monoms->InsertBegin(000, 0);
}

Polynom::Polynom(const TList<UINT, double>& _list)
{
  monoms = new TList<UINT, double>(_list);
  monoms->Reset();
  while (!monoms->IsEnded())
  {
    if (monoms->getCurrentNodeKey() > MAX_KEY)
    {
      //TODO: exception
    }
    monoms->Next();
  }
  monoms->Reset();
}

Polynom::Polynom(const Polynom & _polynom)
{
  monoms = new TList<UINT, double>(*_polynom.monoms);
}

Polynom::~Polynom()
{
  delete monoms;
}

Polynom & Polynom::operator=(const Polynom & _polynom)
{
  delete monoms;
  monoms = new TList<UINT, double>(*_polynom.monoms);
  return *this;
}

Polynom Polynom::operator+(const Polynom & _polynom) const
{
  Polynom result;
  Polynom tmp(*this);
  _polynom.monoms->Reset();
  tmp.monoms->Reset();
  while (!monoms->IsEnded() || !_polynom.monoms->IsEnded())
  {
    UINT currentTmpKey = tmp.monoms->getCurrentNodeKey();
    if (currentTmpKey == _polynom.monoms->getCurrentNodeKey())
    {
      double newData = tmp.monoms->getCurrentNodeData() + _polynom.monoms->getCurrentNodeData();
      if (newData != 0)
        result.monoms->InsertEnd(currentTmpKey, newData);
      tmp.monoms->Next();
      _polynom.monoms->Next();
    } 
    else if (currentTmpKey > _polynom.monoms->getCurrentNodeKey())
    {
      result.monoms->InsertEnd(_polynom.monoms->getCurrentNodeKey(), _polynom.monoms->getCurrentNodeData());
      _polynom.monoms->Next();
    }
    else
    {
      result.monoms->InsertEnd(tmp.monoms->getCurrentNodeKey(), tmp.monoms->getCurrentNodeData());
      tmp.monoms->Next();
    }
  }
  _polynom.monoms->Reset();
  //result.deleteZeros();    //TODO: method in Polynom : deleteZeros()
  return result;
}

Polynom Polynom::operator+(const TNode<UINT, double>& _monom) const
{
  if (_monom.key > MAX_KEY)
  {
    //TODO: exception
  }
  Polynom result(*this);
  UINT currentKey = result.monoms->getCurrentNodeKey();
  while ((currentKey < _monom.key) && (!result.monoms->IsEnded()))
  {
    result.monoms->Next();
    currentKey = result.monoms->getCurrentNodeKey();
  }
  if (currentKey < _monom.key)
    result.monoms->InsertEnd(_monom.key, _monom.pData);
  if (currentKey == _monom.key)
  {
    double newData = result.monoms->getCurrentNodeData() + _monom.pData;
    if (newData != 0)
      result.monoms->InsertAfter(currentKey, _monom.key, newData);
    result.monoms->Remove(currentKey);
  }
  if (currentKey > _monom.key)
    result.monoms->InsertBefore(currentKey, _monom.key, _monom.pData);
  result.monoms->Reset();
  //result.deleteZeros();    //TODO: method in Polynom : deleteZeros()
  return result;
}

Polynom Polynom::operator-(const Polynom & _polynom) const
{
  return Polynom();
}

Polynom Polynom::operator-(const TNode<UINT, double>& _monom) const
{
  return Polynom(Polynom(*this) + TNode<UINT, double>(_monom.key, -_monom.pData));
}

Polynom Polynom::operator*(const Polynom & _polynom) const
{
  return Polynom();
}

Polynom Polynom::operator*(const TNode<UINT, double>& _monom) const
{
  return Polynom();
}
