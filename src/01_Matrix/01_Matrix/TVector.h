#ifndef __TVECTOR_H__
#define __TVECTOR_H__

#include <cmath>
#include <iostream>
#include "MyExceptions.h"

template<typename ValType>
class TVector
{
  protected:
    int size;
    int startIndex;
    ValType* elems;
  
  public:
    TVector(int size = 10, int startIndex = 0);
    TVector(const TVector<ValType>& _tvector);
    ~TVector();

    bool operator==(const TVector<ValType>& _tvector) const;
    bool operator!=(const TVector<ValType>& _tvector) const;

    TVector<ValType>& operator=(const TVector<ValType>& _tvector);
    TVector<ValType> operator+(ValType _value);
    TVector<ValType> operator-(ValType _value);
    TVector<ValType> operator*(ValType _value);
    TVector<ValType> operator+(const TVector<ValType>& _tvector);
    TVector<ValType> operator-(const TVector<ValType>& _tvector);
    ValType operator*(const TVector<ValType>& _tvector);

    ValType& operator[](int index);
    const ValType& operator[](int index) const;

    int getStartIndex() const;
    int getSize() const;
    double length() const;

    friend std::ostream& operator<<(std::ostream& out, const TVector<ValType>& _vector);
    friend std::istream& operator>>(std::istream& in, TVector<ValType>& _vector);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template<typename ValType>
TVector<ValType>::TVector(int _size, int _startIndex) 
  : size(_size), startIndex(_startIndex)
{
  //if (size == 0) throw VectorInvalidSize();
  elems = new ValueType[size];
}

template<typename ValType>
TVector<ValType>::TVector(const TVector<ValType>& _tvector)
  : size(_tvector.size), startIndex(_tvector.startIndex)
{
  elems = new ValType[size];
  memcpy(elems, _tvector.elems, size * sizeof(ValType));
}

template<typename ValType>
TVector<ValType>::~TVector()
{
  if (size > 0)
    delete[] elems;
}

template<typename ValType>
bool TVector<ValType>::operator==(const TVector<ValType>& _tvector) const
{
  if (size != _tvector.size)
    return false;
  for (int i = 0; i < size; i++)
    if (elems[i] != _tvector.elems[i])
      return false;
  return true;
}

template<typename ValType>
bool TVector<ValType>::operator!=(const TVector<ValType>& _tvector) const
{
  if (size != _tvector.size)                 //return !(*this == _tvector);
    return true;
  for (int i = 0; i < size; i++)
    if (elems[i] != _tvector.elems[i])
      return true;
  return false;
}

template<typename ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& _tvector)
{
  if (this == &_tvector)
    return *this;
  if (size != _tvector.size)
  {
    delete[] elems;
    elems = new ValueType[_tvector.size];
  }
  size = _tvector.size;
  startIndex = _tvector.startIndex;
  memcpy(elems, _tvector.elems, size * sizeof(ValueType));
  return *this;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+(ValType _value)
{
  TVector<ValType> result(*this);
  for (int i = 0; i < size; i++)
    result.elems[i] += _value;
  return result;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(ValType _value)
{
  TVector<ValType> result(*this);
  for (int i = 0; i < size; i++)
    result.elems[i] -= _value;
  return result;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator*(ValType _value)
{
  TVector<ValType> result(*this);
  for (int i = 0; i < size; i++)
    result.elems[i] *= _value;
  return result;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& _tvector)
{
  if (size != _tvector.size)
    throw VectorDifferentSizes();
  TVector<ValType> result(*this);
  for (int i = 0; i < size; i++)
    result.elems[i] = result.elems[i] + _tvector.elems[i];
  return result;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& _tvector)
{
  if (size != _tvector.size)
    throw VectorDifferentSizes();
  TVector<ValType> result(*this);
  for (int i = 0; i < size; i++)
    result.elems[i] = result.elems[i] - _tvector.elems[i];
  return result;
}

template<typename ValType>
ValType TVector<ValType>::operator*(const TVector<ValType>& _tvector)
{
  if (size != _tvector.size)
    throw VectorDifferentSizes();
  ValType scalarProduct(0);
  for (int i = 0; i < size; i++)
    scalarProduct += elems[i] * _tvector.elems[i];
  return scalarProduct;
}

template<typename ValType>
ValType& TVector<ValType>::operator[](int index)
{
  if (index - startIndex >= size)
    throw std::out_of_range("AAAAAAAA!");
  return elements[index - startIndex];
}

template<typename ValType>
const ValType& TVector<ValType>::operator[](int index) const
{
  if (index - startIndex >= size)
    throw std::out_of_range("AAAAAAAA!");
  return elems[index - startIndex];
}

template<typename ValType>
int TVector<ValType>::getStartIndex() const
{
    return startIndex;
}

template<typename ValType>
int TVector<ValType>::getSize() const
{
    return size;
}

template<typename ValType>
double TVector<ValType>::length() const
{
  ValType scalarProduct(0);
  for (int i = 0; i < size; i++)
    scalarProduct += elems[i] * elems[i];
  return sqrt(scalarProduct);               //return sqrt((*this) * (*this))
}

template<typename ValType>
std::ostream & operator<<(std::ostream & out, const TVector<ValType> & _vector)
{
  out << "[ ";
  if (_vector.size == 0)
    return out << ']';
  for (int i = 0; i < _vector.startIndex; i++)
    out << std::setw(5) << std::setprecision(2) << std::right << ValType(0) << ' ';
  for (int i = 0; i < _vector.size; i++)
    out << std::setw(5) << std::setprecision(2) << std::right << _vector.elems[i] << ' ';
  return out << ']';
}

template<typename ValType>
std::istream & operator>>(std::istream & in, TVector<ValType> & _vector)
{
  if (_vector.size == 0)
    return in;
  for (int i = 0; i < _vector.size; i++)
    in >> vector.elems[i];
  return in;
}

#endif // !__TVECTOR_H__