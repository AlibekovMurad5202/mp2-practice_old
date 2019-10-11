#ifndef __TVECTOR_H__
#define __TVECTOR_H__

#include <cmath>
#include <iostream>
#include <iomanip>
#include "MyExceptions.h"

template<typename ValType>
class TVector
{ 
  protected:
    int size;
    int startIndex;
    ValType* elems;
  
  public:
    explicit TVector(int size = 5, int startIndex = 0);
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
    ValType length() const;

    friend std::ostream& operator<<(std::ostream& out, const TVector<ValType>& _vector)
    {
      out << "[ ";
      if (_vector.size != 0)
      {
        for (int i = 0; i < _vector.startIndex; i++)
          out << std::setw(5) << std::setprecision(2) << std::right << ValType(0) << ' ';
        for (int i = 0; i < _vector.size; i++)
          out << std::setw(5) << std::setprecision(2) << std::right << _vector.elems[i] << ' ';
      }
      out << ']';
      return out;
    }

    friend std::istream& operator>>(std::istream& in, TVector<ValType>& _vector)
    {
      if (_vector.size != 0)
        for (int i = 0; i < _vector.size; i++)
          in >> _vector.elems[i];
      return in;
    }
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template<typename ValType>
TVector<ValType>::TVector(int _size, int _startIndex) 
  : size(_size), startIndex(_startIndex)
{
  if (size <= 0) 
  {
    VectorExceptionNotPositiveDimension e(__LINE__, __FILE__);
    throw e;
  }
  elems = new ValType[size];
}

template<typename ValType>
TVector<ValType>::TVector(const TVector<ValType>& _tvector)
  : size(_tvector.size), startIndex(_tvector.startIndex)
{
  if (size <= 0)
  {
    VectorExceptionNotPositiveDimension e(__LINE__, __FILE__);
    throw e;
  }
  elems = new ValType[size];
  for (int i = 0; i < size; i++)
    elems[i] = _tvector.elems[i];
}

template<typename ValType>
TVector<ValType>::~TVector()
{
  delete[] elems;
}

template<typename ValType>
bool TVector<ValType>::operator==(const TVector<ValType>& _tvector) const
{
  if ((size != _tvector.size) || (startIndex != _tvector.startIndex))
    return false;
  for (int i = 0; i < size; i++)
    if (elems[i] != _tvector.elems[i])
      return false;
  return true;
}

template<typename ValType>
bool TVector<ValType>::operator!=(const TVector<ValType>& _tvector) const
{
  return !(*this == _tvector);
}

template<typename ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& _tvector)
{
  if (this == &_tvector)
    return *this;
  if (size != _tvector.size)
  {
    delete[] elems;
    size = _tvector.size;
    elems = new ValType[size];
  }
  startIndex = _tvector.startIndex;
  for (int i = 0; i < size; i++)
      elems[i] = _tvector.elems[i];
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
  if ((size != _tvector.size) || (startIndex != _tvector.startIndex))
  {
    VectorExceptionDifferentDimensions e(__LINE__, __FILE__);
    throw e;
  }
  TVector<ValType> result(*this);
  for (int i = 0; i < size; i++)
    result.elems[i] += _tvector.elems[i];
  return result;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& _tvector)
{
  if ((size != _tvector.size) || (startIndex != _tvector.startIndex))
  {
    VectorExceptionDifferentDimensions e(__LINE__, __FILE__);
    throw e;
  }
  TVector<ValType> result(*this);
  for (int i = 0; i < size; i++)
    result.elems[i] -= _tvector.elems[i];
  return result;
}

template<typename ValType>
ValType TVector<ValType>::operator*(const TVector<ValType>& _tvector)
{
  if ((size != _tvector.size) || (startIndex != _tvector.startIndex))
  {
    VectorExceptionDifferentDimensions e(__LINE__, __FILE__);
    throw e;
  }
  ValType scalarProduct;
  scalarProduct = ValType(0);
  for (int i = 0; i < size; i++)
    scalarProduct += elems[i] * _tvector.elems[i];
  return scalarProduct;
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
ValType TVector<ValType>::length() const
{
  return sqrt((*this) * (*this));
}

template<typename ValType>
ValType& TVector<ValType>::operator[](int _index)
{
  if ((_index < startIndex) || (_index - startIndex >= size)) {
    VectorExceptionOutOfRange e(__LINE__, __FILE__);
    throw e;
  }
  return elems[_index - startIndex];
}

template<typename ValType>
const ValType& TVector<ValType>::operator[](int _index) const
{
  if ((_index < startIndex) || (_index - startIndex >= size)) {
    VectorExceptionOutOfRange e(__LINE__, __FILE__);
    throw e;
  }
  return elems[_index - startIndex];
};

#endif // !__TVECTOR_H__