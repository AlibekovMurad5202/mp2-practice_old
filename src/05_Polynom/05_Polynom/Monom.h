#ifndef __MONOM_H__
#define __MONOM_H__

#include "TNode.h"
#include "MyExceptions.h"
#include "iostream"
#include "string"

#define MAX_KEY 999
#define MAX_DEGREE 9
#define UINT unsigned int

//~~~~~~~~~~~~~~~~~~~~~~~~ struct Monom ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#define Monom TNode<UINT, double>

template<>
struct Monom
{
  UINT key;
  double data;
  Monom* pNext;

  TNode();
  TNode(UINT _key, double _data);
  TNode(double _data);
  TNode(const Monom& _monom);
  ~TNode();

  const Monom& operator=(const Monom& _monom);

  Monom operator+(const Monom& _monom);
  Monom operator-(const Monom& _monom);
  Monom operator*(const Monom& _monom);

  char signOfCoefficient();

  friend std::ostream& operator<<(std::ostream& out, const Monom& _monom);
  static Monom convert(const std::string& _monom);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

Monom::TNode()
  : pNext(nullptr), key(0), data(.0)
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

Monom::TNode(double _data)
  : key(0), data(_data), pNext(nullptr)
{
}

Monom::TNode(const Monom& _monom)
{
  if (&_monom != nullptr)
  {
  key = _monom.key;
  data = _monom.data;
  pNext = nullptr;

  }
  else
  {
    key = 0;
    data = .0;
    pNext = nullptr;
  }
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

inline char Monom::signOfCoefficient()
{
  if (data > 0)
    return '+';
  if (data < 0)
    return '-';
  return 0;
}

Monom Monom::convert(const std::string & _monom)
{
  UINT key;
  double data;
   
  std::string new_monom;
  for (int i = 0; i < _monom.length(); i++)
    if ((_monom[i] != ' ') && (_monom[i] != '*') && (_monom[i] != '+') && (_monom[i] != '-'))
      new_monom.push_back(_monom[i]);
  std::string coef;
  UINT x_degree = 0;
  UINT y_degree = 0;
  UINT z_degree = 0;

  int j = 0;
  if ((new_monom[j] == 'x') || (new_monom[j] == 'y') || (new_monom[j] == 'z'))
    coef.push_back('1');
  else
    while ((new_monom[j] != 'x') && (new_monom[j] != 'y')
      && (new_monom[j] != 'z') && (new_monom.length() - j))
      coef.push_back(new_monom[j++]);

  if ((!coef.empty()) && (coef.find_first_not_of("0123456789.") == coef.npos))
    data = std::stod(coef);
  else throw ExceptionWrongExpression(__LINE__, __FILE__);

  for (int i = j; i < new_monom.length(); i++)
  {
    switch (new_monom[i])
    {
    case 'x':
    {
      if (new_monom[i + 1] == '^')
        if (('0' <= new_monom[i + 2]) && (new_monom[i + 2] <= '9'))
          if (x_degree + new_monom[i + 2] - '0' > MAX_DEGREE)
            throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
          else
          {
            x_degree += new_monom[i + 2] - '0';
            i += 2;
          }
        else throw ExceptionWrongExpression(__LINE__, __FILE__);
      else if ((new_monom[i + 1] == 'y') || (new_monom[i + 1] == 'z') || (new_monom[i + 1] == 0))
        if (x_degree + 1 > MAX_DEGREE)
          throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
        else x_degree++;
      else if ((i + 1 >= new_monom.length()) || (new_monom[i + 1] == ' ')
        || (new_monom[i + 1] == '+') || (new_monom[i + 1] == '*'))
        x_degree++;
      else
        throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
      break;
    }
    case 'y':
    {
      if (new_monom[i + 1] == '^')
        if (('0' <= new_monom[i + 2]) && (new_monom[i + 2] <= '9'))
          if (y_degree + new_monom[i + 2] - '0' > MAX_DEGREE)
            throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
          else
          {
            y_degree += new_monom[i + 2] - '0';
            i += 2;
          }
        else throw ExceptionWrongExpression(__LINE__, __FILE__);
      else if ((new_monom[i + 1] == 'x') || (new_monom[i + 1] == 'z') || (new_monom[i + 1] == 0))
        if (y_degree + 1 > MAX_DEGREE)
          throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
        else y_degree++;
      else if ((i + 1 >= new_monom.length()) || (new_monom[i + 1] == ' ')
        || (new_monom[i + 1] == '+') || (new_monom[i + 1] == '*'))
        y_degree++;
      else throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
      break;
    }
    case 'z':
    {
      if (new_monom[i + 1] == '^')
        if (('0' <= new_monom[i + 2]) && (new_monom[i + 2] <= '9'))
          if (z_degree + new_monom[i + 2] - '0' > MAX_DEGREE)
            throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
          else
          {
            z_degree += new_monom[i + 2] - '0';
            i += 2;
          }
        else throw ExceptionWrongExpression(__LINE__, __FILE__);
      else if ((new_monom[i + 1] == 'x') || (new_monom[i + 1] == 'y') || (new_monom[i + 1] == 0))
        if (z_degree + 1 > MAX_DEGREE)
          throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
        else z_degree++;
      else if ((i + 1 >= new_monom.length()) || (new_monom[i + 1] == ' ')
        || (new_monom[i + 1] == '+') || (new_monom[i + 1] == '*'))
        z_degree++;
      else throw ExceptionMonomDoesNotExist(__LINE__, __FILE__);
      break;
    }
    default: throw ExceptionWrongExpression(__LINE__, __FILE__);
      break;
    }
  }
  key = x_degree * 100 + y_degree * 10 + z_degree;
  return Monom(key, data);
}

std::ostream& operator<<(std::ostream& out, const Monom& _monom)
{
  if (_monom.data > 0) out << " +";
  else if (_monom.data < 0) out << " -";
  else return out;

  if ((_monom.key == 0) || (abs(_monom.data) != 1))
    out << " " << abs(_monom.data);

  if (_monom.key / 100 == 1)
    out << (_monom.data != 1 ? " * x" : " x");
  else if (_monom.key / 100 != 0)
    out << (_monom.data != 1 ? " * x^" : " x^") << _monom.key / 100;

  if ((_monom.key % 100) / 10 == 1)
    out << (_monom.data != 1 || (_monom.key / 100) ? " * y" : " y");
  else if ((_monom.key % 100) / 10 != 0)
    out << (_monom.data != 1 || (_monom.key / 100) ? " * y^" : " y^") << _monom.key % 100 / 10;

  if (_monom.key % 10 == 1)
    out << (_monom.data != 1 || (_monom.key / 100) || ((_monom.key % 100) / 10) ? " * z" : " z");
  else if (_monom.key % 10 != 0)
    out << (_monom.data != 1 || (_monom.key / 100) || ((_monom.key % 100) / 10) ? " * z^" : " z^") << _monom.key % 10;

  return out;
};

#endif // !__MONOM_H__