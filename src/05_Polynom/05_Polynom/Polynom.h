#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include "TList.h"

class Polynom
{
protected:
  TList<UINT, double> *monoms;

public:
  Polynom();
  Polynom(const TList<UINT, double>& _list);
  Polynom(const Polynom& _polynom);
  ~Polynom();

  Polynom& operator=(const Polynom& _polynom);

  Polynom operator+(const Polynom& _polynom) const;
  Polynom operator+(const Monom& _monom) const;

  Polynom operator-(const Polynom& _polynom) const;
  Polynom operator-(const Monom& _monom) const;

  Polynom operator*(const Polynom& _polynom) const;
  Polynom operator*(const Monom& _monom) const;

  friend std::ostream& operator<<(std::ostream& out, const Polynom& _polynom);
  //friend std::istream& operator>>(std::istream& in, Polynom& _polynom);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

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
      throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
    monoms->Next();
  }
  monoms->Reset();
}

Polynom::Polynom(const Polynom& _polynom)
{
  monoms = new TList<UINT, double>(*_polynom.monoms);
}

Polynom::~Polynom()
{
  delete monoms;
}

Polynom & Polynom::operator=(const Polynom& _polynom)
{
  delete monoms;
  monoms = new TList<UINT, double>(*_polynom.monoms);
  return *this;
}

Polynom Polynom::operator+(const Polynom& _polynom) const
{
  Polynom result;
  _polynom.monoms->Reset();
  monoms->Reset();
  while (!monoms->IsEnded() || !_polynom.monoms->IsEnded())
  {
    Monom m1(monoms->getCurrentNodeKey(), monoms->getCurrentNodeData());
    Monom m2(_polynom.monoms->getCurrentNodeKey(), _polynom.monoms->getCurrentNodeData());
    if (m1.key = m2.key)
    {
      Monom sum = m1 + m2;
      if (sum.data != 000)
        result.monoms->InsertEnd(sum);
      monoms->Next();
      _polynom.monoms->Next();
    }
    else if (m1.key > m2.key)
    {
      result.monoms->InsertEnd(m2);
      _polynom.monoms->Next();
    }
    else
    {
      result.monoms->InsertEnd(m1);
      monoms->Next();
    }
  }
  _polynom.monoms->Reset();
  monoms->Reset();
  //result.deleteZeros();    //TODO: method in Polynom : deleteZeros()
  return result;
}

Polynom Polynom::operator+(const Monom& _monom) const
{
  Polynom result(*this);
  UINT currentKey = result.monoms->getCurrentNodeKey();
  while ((currentKey < _monom.key) && (!result.monoms->IsEnded()))
  {
    result.monoms->Next();
    currentKey = result.monoms->getCurrentNodeKey();
  }
  if (currentKey < _monom.key)
    result.monoms->InsertEnd(_monom.key, _monom.data);
  if (currentKey == _monom.key)
  {
    double newData = result.monoms->getCurrentNodeData() + _monom.data;
    if (newData != 0)
      result.monoms->InsertAfter(currentKey, _monom.key, newData);
    result.monoms->Remove(currentKey);
  }
  if (currentKey > _monom.key)
    result.monoms->InsertBefore(currentKey, _monom.key, _monom.data);
  result.monoms->Reset();
  //result.deleteZeros();    //TODO: method in Polynom : deleteZeros()
  return result;
}

Polynom Polynom::operator-(const Polynom & _polynom) const
{
  return (Polynom(*this) + _polynom * Monom(000, -1));
}

Polynom Polynom::operator-(const Monom& _monom) const
{
  return Polynom(Polynom(*this) + Monom(_monom.key, -_monom.data));
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
    Polynom tmp(Polynom(*this) * Monom(currentKey, currentData));
    result = result + tmp;
    _polynom.monoms->Next();
  }
  _polynom.monoms->Reset();
  monoms->Reset();
  //result.deleteZeros();    //TODO: method in Polynom : deleteZeros()
  return result;
}

Polynom Polynom::operator*(const Monom& _monom) const
{
  Polynom result;
  if (_monom.data == 0)
    return result;
  while (!monoms->IsEnded())
  {
    Monom tmp(monoms->getCurrentNodeKey(), monoms->getCurrentNodeData());
    result.monoms->InsertEnd(tmp * _monom);
  }
  monoms->Reset();
  return result;
}

std::ostream& operator<<(std::ostream& out, const Polynom& _polynom)
{
  _polynom.monoms->Reset();
  if (_polynom.monoms->IsEmpty())
    out << 0;
  else 
    while (!_polynom.monoms->IsEnded())
    {
      out << Monom(_polynom.monoms->getCurrentNodeKey(), _polynom.monoms->getCurrentNodeData());
      _polynom.monoms->Next();
    }
  return out;
}

#endif // !__POLYNOM_H__