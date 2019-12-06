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
  _polynom.monoms->Reset();
  monoms->Reset();
  while (!monoms->IsEnded() || !_polynom.monoms->IsEnded())
  {
    UINT currentKey = monoms->getCurrentNodeKey();
    if (currentKey == _polynom.monoms->getCurrentNodeKey())
    {
      double newData = monoms->getCurrentNodeData() + _polynom.monoms->getCurrentNodeData();
      if (newData != 0)
        result.monoms->InsertEnd(currentKey, newData);
      monoms->Next();
      _polynom.monoms->Next();
    } 
    else if (currentKey > _polynom.monoms->getCurrentNodeKey())
    {
      result.monoms->InsertEnd(_polynom.monoms->getCurrentNodeKey(), _polynom.monoms->getCurrentNodeData());
      _polynom.monoms->Next();
    }
    else
    {
      result.monoms->InsertEnd(monoms->getCurrentNodeKey(), monoms->getCurrentNodeData());
      monoms->Next();
    }
  }
  _polynom.monoms->Reset();
  monoms->Reset();
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
  return (*this + _polynom * TNode<UINT, double>(000, -1));
}

Polynom Polynom::operator-(const TNode<UINT, double>& _monom) const
{
  return Polynom(Polynom(*this) + TNode<UINT, double>(_monom.key, -_monom.pData));
}

Polynom Polynom::operator*(const Polynom & _polynom) const
{
  Polynom result;
  _polynom.monoms->Reset();
  monoms->Reset();
  while (!_polynom.monoms->IsEnded())
  {
    double currentData = _polynom.monoms->getCurrentNodeData();
    UINT currentKey = _polynom.monoms->getCurrentNodeKey();
    Polynom tmp(*this * TNode<UINT, double>(currentKey, currentData));
    result = result + tmp;
    _polynom.monoms->Next();
  }
  _polynom.monoms->Reset();
  monoms->Reset();
  //result.deleteZeros();    //TODO: method in Polynom : deleteZeros()
  return result;
}

Polynom Polynom::operator*(const TNode<UINT, double>& _monom) const
{
  Polynom result;
  if (_monom.pData == 0)
    return result;
  while (!monoms->IsEnded())
  {
    double newData = monoms->getCurrentNodeData() * _monom.pData;
    UINT currentKey = monoms->getCurrentNodeKey();
    UINT newKey = 000;
    if (((currentKey / 100) + (_monom.key / 100) > MAX_DEGREE)
      || ((currentKey % 10) + (_monom.key % 10) > MAX_DEGREE)
      || (((currentKey % 100) / 10) + ((_monom.key % 100) / 10)) > MAX_DEGREE)
    {
      //TODO: exception
    }
    newKey = monoms->getCurrentNodeKey() + _monom.key;
    result.monoms->InsertEnd(newKey, newData);
  }
  monoms->Reset();
  return result;
}
