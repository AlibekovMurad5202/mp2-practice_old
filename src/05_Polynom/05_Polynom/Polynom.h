#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include "TList.h"

class Polynom
{
protected:
  TList<UINT, double> *monoms;

public:

  //TODO: 
  //  void Sort();
  //  Polynom(const std::string& _polynom);

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
  Polynom p1(*this);
  Polynom p2(_polynom);
  p2.monoms->Reset();
  p1.monoms->Reset();
  while (!p1.monoms->IsEnded() || !p2.monoms->IsEnded())
  {
    Monom m1(p1.monoms->getCurrentNodeKey(), p1.monoms->getCurrentNodeData());
    Monom m2(p2.monoms->getCurrentNodeKey(), p2.monoms->getCurrentNodeData());
    if (m1.key = m2.key)
    {
      Monom sum = m1 + m2;
      if (sum.data != 000)
        result.monoms->InsertEnd(sum);
      p1.monoms->Next();
      p2.monoms->Next();
    }
    else if (m1.key > m2.key)
    {
      result.monoms->InsertEnd(m2);
      p2.monoms->Next();
    }
    else
    {
      result.monoms->InsertEnd(m1);
      p1.monoms->Next();
    }
  }
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
  return (Polynom(*this) + Monom(_monom.key, -_monom.data));
}

Polynom Polynom::operator*(const Polynom & _polynom) const
{
  Polynom result;
  Polynom polynomial(_polynom);
  polynomial.monoms->Reset();
  while (!polynomial.monoms->IsEnded())
  {
    double currentData = polynomial.monoms->getCurrentNodeData();
    UINT currentKey = polynomial.monoms->getCurrentNodeKey();
    Polynom tmp(Polynom(*this) * Monom(currentKey, currentData));
    result = result + tmp;
    polynomial.monoms->Next();
  }
  //result.deleteZeros();    //TODO: method in Polynom : deleteZeros()
  return result;
}

Polynom Polynom::operator*(const Monom& _monom) const
{
  Polynom result;
  Polynom polynomial(*this);
  if (_monom.data == 0)
    return result;
  while (!polynomial.monoms->IsEnded())
  {
    Monom tmp(polynomial.monoms->getCurrentNodeKey(), polynomial.monoms->getCurrentNodeData());
    result.monoms->InsertEnd(tmp * _monom);
  }
  return result;
}

std::ostream& operator<<(std::ostream& out, const Polynom& _polynom)
{
  _polynom.monoms->Reset();
  if (_polynom.monoms->IsEmpty())
    out << " 0 ";
  else 
    while (!_polynom.monoms->IsEnded())
    {
      out << Monom(_polynom.monoms->getCurrentNodeKey(), _polynom.monoms->getCurrentNodeData());
      _polynom.monoms->Next();
    }
  return out;
}

#endif // !__POLYNOM_H__