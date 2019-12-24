#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include "TList.h"
#include "string"
#include "iostream"

class Polynom
{
protected:
  TList<UINT, double> *monoms;

public:

  Polynom();
  Polynom(const TList<UINT, double>& _list);
  Polynom(const Monom& _monom);
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
  friend std::istream& operator>>(std::istream& in, Polynom& _polynom);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

Polynom::Polynom()
{
  monoms = new TList<UINT, double>;
  monoms->InsertBegin(0, .0);
}

Polynom::Polynom(const TList<UINT, double>& _list)
{
  monoms = new TList<UINT, double>();
  monoms->InsertEnd(0, .0);
  TList<UINT, double> *tmp_list = new TList<UINT, double>(_list);
  tmp_list->Reset();
  while (!tmp_list->IsEnded())
  {
    if (tmp_list->getCurrentNodeKey() > MAX_KEY)
      throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
    *this = *this + Monom(tmp_list->getCurrentNodeKey(), tmp_list->getCurrentNodeData());
    tmp_list->Next();
  }
  tmp_list->Reset();
  delete tmp_list;

}

Polynom::Polynom(const Monom & _monom)
{
  monoms = new TList<UINT, double>();
  monoms->InsertBegin(_monom.key, _monom.data);
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
  p1.monoms->Reset();
  p2.monoms->Reset();
  
  while (!p1.monoms->IsEnded() && !p2.monoms->IsEnded())
  {
    Monom m1 = Monom(p1.monoms->getCurrentNodeKey(), p1.monoms->getCurrentNodeData());
    Monom m2 = Monom(p2.monoms->getCurrentNodeKey(), p2.monoms->getCurrentNodeData());
    if (m1.key == m2.key)
    {
      Monom sum = m1 + m2;
      if (sum.data != 0)
        result = result + sum;
      p1.monoms->Next();
      p2.monoms->Next();
    }
    else if (m1.key > m2.key)
    {
      result = result + m2;
      p2.monoms->Next();
    }
    else
    {
      result = result + m1;
      p1.monoms->Next();
    }
  }
  
  while (!p1.monoms->IsEnded())
  {
    Monom m1 = Monom(p1.monoms->getCurrentNodeKey(), p1.monoms->getCurrentNodeData());
    result = result + m1;
    p1.monoms->Next();
  }

  while (!p2.monoms->IsEnded())
  {
    Monom m2 = Monom(p2.monoms->getCurrentNodeKey(), p2.monoms->getCurrentNodeData());
    result = result + m2;
    p2.monoms->Next();
  }

  return result;
}

Polynom Polynom::operator+(const Monom& _monom) const
{
  if (this->monoms->IsEmpty())
  {
    TList<UINT, double> tmp;
    tmp.InsertBegin(0, .0);
    return Polynom(tmp);
  }
  Polynom result(*this);
  result.monoms->Reset();
  UINT currentKey = result.monoms->getCurrentNodeKey();
  while ((currentKey < _monom.key) && (!result.monoms->IsEnded()))
  {
    result.monoms->Next();
    if (!result.monoms->IsEnded())
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
  return result;
}

Polynom Polynom::operator-(const Polynom & _polynom) const
{
  return (Polynom(*this) + _polynom * (-1.));
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
  return result;
}

Polynom Polynom::operator*(const Monom& _monom) const
{
  Polynom result;
  Polynom polynomial(*this);
  if (_monom.data == 0)
    return result;
  polynomial.monoms->Reset();
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
  {
    if (_polynom.monoms->getCurrentNodeData() == 0)
      _polynom.monoms->Next();
    if (_polynom.monoms->IsEnded())
    {
      out << " 0 ";
      return out;
    }

    Monom tmp(_polynom.monoms->getCurrentNodeKey(), _polynom.monoms->getCurrentNodeData());
    out << " ";
    if (tmp.signOfCoefficient() < 0)
      out << "- ";

    if ((tmp.key == 0) || (abs(tmp.data) != 1))
      out << abs(tmp.data);

    if (tmp.key / 100 == 1)
      out << (tmp.data != 1 ? " * x" : " x");
    else if (tmp.key / 100 != 0)
      out << (tmp.data != 1 ? " * x^" : " x^") << tmp.key / 100;

    if ((tmp.key % 100) / 10 == 1)
      out << (tmp.data != 1 || (tmp.key / 100) ? " * y" : " y");
    else if ((tmp.key % 100) / 10 != 0)
      out << (tmp.data != 1 || (tmp.key / 100) ? " * y^" : " y^") << tmp.key % 100 / 10;

    if (tmp.key % 10 == 1)
      out << (tmp.data != 1 || (tmp.key / 100) || ((tmp.key % 100) / 10) ? " * z" : " z");
    else if (tmp.key % 10 != 0)
      out << (tmp.data != 1 || (tmp.key / 100) || ((tmp.key % 100) / 10) ? " * z^" : " z^") << tmp.key % 10;

    _polynom.monoms->Next();
    while (!_polynom.monoms->IsEnded())
    {
      Monom tmp = Monom(_polynom.monoms->getCurrentNodeKey(), _polynom.monoms->getCurrentNodeData());
      if (tmp.signOfCoefficient() > 0)
        out << " +";
      out << tmp;
      _polynom.monoms->Next();
    }
  }
  return out;
}

std::istream& operator>>(std::istream& in, Polynom& _polynom)
{
  delete _polynom.monoms;
  _polynom.monoms = new TList<UINT, double>;

  std::string line;
  std::getline(in, line);
  int lengthOfExpression = int(line.length());
  _polynom = _polynom + (0.);


  while (lengthOfExpression)
  {
    char _sign = '+';   // '+' ~ 43; '-' ~ 45
    int start;
    int end;
    std::string s_monom;
    enum Prev { sign, monom, other } p;
    p = Prev::other;

    for (int i = 0; i < lengthOfExpression; i++)
    {
      if (line[i] == ' ');
      else if ((line[i] == '+') || (line[i] == '-'))
      {
        if (p == Prev::sign)
          throw ExceptionWrongExpression(__LINE__, __FILE__);
        p = Prev::sign;
        _sign = line[i];
      }
      else if ((line[i] == 'x') || (line[i] == 'y') || (line[i] == 'z')
        || (('0' <= line[i]) && (line[i] <= '9')))
      {
        if (p == Prev::monom)
          throw ExceptionWrongExpression(__LINE__, __FILE__);
        p = Prev::monom;
        start = i;
        for (end = i; ((line[end] != '+') && (line[end] != '-') && (end < lengthOfExpression)); end++);
        break;
      }
      else throw ExceptionWrongExpression(__LINE__, __FILE__);
    }
    s_monom = line.substr(start, end - start + 1);
    _polynom = _polynom + Monom().convert(s_monom) * (44 - _sign);

    if (lengthOfExpression - end <= 0)
      break;

    line = line.substr(end + 1, lengthOfExpression - end);
    lengthOfExpression = int(line.length());
  }

  return in;
}

#endif // !__POLYNOM_H__