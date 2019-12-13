#ifndef __MONOM_H__
#define __MONOM_H__

#include "TNode.h"
#include "MyExceptions.h"

#define MAX_KEY 999
#define MAX_DEGREE 9
#define UINT unsigned int

//~~~~~~~~~~~~~~~~~~~~~~~~ struct Monom ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#define Monom TNode<UINT, double>

template<>
struct Monom// : public TNode<UINT, double>
{
  UINT key;
  double data;
  Monom* pNext;

  TNode();
  TNode(UINT _key, double _data);
  TNode(const Monom& _monom);
  ~TNode();

  const Monom& operator=(const Monom& _monom);

  Monom operator+(const Monom& _monom);
  Monom operator-(const Monom& _monom);
  Monom operator*(const Monom& _monom);

  friend std::ostream& operator<<(std::ostream& out, const Monom& _monom);

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

Monom::TNode()
  : pNext(nullptr), key(000), data(.0)
{
}

Monom::TNode(UINT _key, double _data)
{
  if (_key > MAX_KEY)
    throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
  key = _key;
  data = _data;
  pNext = nullptr;
}

Monom::TNode(const Monom& _monom)
  : key(_monom.key), data(_monom.data), pNext(nullptr)
{
}

Monom::~TNode()
{
  pNext = nullptr;
}

const Monom& Monom::operator=(const Monom& _monom)
{
  if (this != &_monom)
  {
    key = _monom.key;
    data = _monom.data;
  }
  return *this;
}

Monom Monom::operator+(const Monom& _monom)
{
  if (key != _monom.key)
    throw ExceptionDifferentDegrees(__LINE__, __FILE__);
  return Monom(key, data + _monom.data);
}

Monom Monom::operator-(const Monom& _monom)
{
  if (key != _monom.key)
    throw ExceptionDifferentDegrees(__LINE__, __FILE__);
  return Monom(key, data - _monom.data);
}

Monom Monom::operator*(const Monom& _monom)
{
  if ((key / 100 + _monom.key / 100 > MAX_DEGREE)
    || ((key % 100) / 10 + (_monom.key % 100) / 10 > MAX_DEGREE)
    || (key % 10 + _monom.key % 10 > MAX_DEGREE))
    throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
  return Monom(key + _monom.key, data * _monom.data);
}

std::ostream& operator<<(std::ostream& out, const Monom& _monom)
{
  if (_monom.data > 0) out << " + ";
  else out << " - ";
  if ((_monom.key == 0) || (abs(_monom.data) != 1))
    out << abs(_monom.data);
  if (_monom.key / 100 != 0)
    out << " * x^" << _monom.key / 100;
  if ((_monom.key % 100) / 10 != 0)
    out << " * y^" << _monom.key % 100 / 10;
  if (_monom.key % 10 != 0)
    out << " * z^" << _monom.key % 10;
  return out;
};

#endif // !__MONOM_H__