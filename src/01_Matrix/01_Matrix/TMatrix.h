#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include "TVector.h"

template<typename ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  explicit TMatrix(int _size = 5);
  TMatrix(const TMatrix& _tmatrix);
  TMatrix(const TVector<TVector<ValType> >& _matrix);
  ~TMatrix();

  bool operator==(const TMatrix& _tmatrix) const;
  bool operator!=(const TMatrix& _tmatrix) const;

  TMatrix& operator=(const TMatrix& _tmatrix);
  TMatrix operator+(ValType _value);
  TMatrix operator-(ValType _value);
  TMatrix operator*(ValType _value);
  TMatrix operator+(const TMatrix& _tmatrix);
  TMatrix operator-(const TMatrix& _tmatrix);
  TMatrix operator*(const TMatrix& _tmatrix);
  
  TVector<ValType> operator*(const TVector<ValType>& _tvector);

  ValType determinant();

  friend std::ostream& operator<<(std::ostream& out, const TMatrix<ValType>& _tmatrix)
  {
    if (_tmatrix.size == 0)
      return out;
    for (int i = 0; i < _tmatrix.size - 1; i++)
      out << _tmatrix.elems[i] << std::endl;
    out << _tmatrix.elems[_tmatrix.size - 1];
    return out;
  }

  friend std::istream& operator>>(std::istream& in, TMatrix<ValType>& _tmatrix)
  {
    if (_tmatrix.size == 0)
      return in;
    for (int i = 0; i < _tmatrix.size; i++)
    {
      std::cout << "Enter row #" << i + 1 << ": " << std::endl;
      in >> _tmatrix.elems[i];
    }
    return in;
  }
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template<typename ValType>
TMatrix<ValType>::TMatrix(int _size) 
  : TVector<TVector<ValType> >(_size)
{
  for (int i = 0; i < _size; i++)
    this->elems[i] = TVector<ValType>(_size - i, i);
}

template<typename ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& _tmatrix)
  : TVector<TVector<ValType> >(_tmatrix.getSize())
{
  for (int i = 0; i < _tmatrix.size; i++)
    this->elems[i] = _tmatrix.elems[i];
}

template<typename ValType>
inline TMatrix<ValType>::~TMatrix() {}

template<typename ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& _matrix) 
  : TVector<TVector<ValType> >(_matrix.getSize())
{
  for (int i = 0; i < this->size; i++)
  {
    this->elems[i] = TVector<ValType>(this->size - i, i);
    for (int j = i; j < this->size; j++)
      this->elems[i][j] = _matrix[i][j];
  }
}

template<typename ValueType>
bool TMatrix<ValueType>::operator==(const TMatrix<ValueType>& _tmatrix) const
{
  if (this->size != _tmatrix.size)
    return false;
  for (int i = 0; i < _tmatrix.size; i++)
    if (this->elems[i] != _tmatrix.elems[i])
      return false;
  return true;
}

template<typename ValueType>
bool TMatrix<ValueType>::operator!=(const TMatrix<ValueType>& _tmatrix) const
{
  return !(*this == _tmatrix);
}

template<typename ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& _tmatrix)
{
  if (this == &_tmatrix)
    return *this;
  if (this->size != _tmatrix.size)
  {
    this->size = _tmatrix.size;
    delete[] this->elems;
    this->elems = new TVector<ValType>[_tmatrix.size];
  }
  for (int i = 0; i < _tmatrix.size; i++)
    this->elems[i] = _tmatrix.elems[i];
  return *this;
}
           
template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(ValType _value)
{
  TMatrix<ValType> result(*this);
  for (int i = 0; i < result.size; i++)
    result.elems[i] = this->elems[i] + _value;
  return result;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(ValType _value)
{
  TMatrix<ValType> result(*this);
  for (int i = 0; i < result.size; i++)
    result.elems[i] = this->elems[i] - _value;
  return result;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(ValType _value)
{
  TMatrix<ValType> result(*this);
  for (int i = 0; i < result.size; i++)
    result.elems[i] = this->elems[i] * _value;
  return result;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& _tmatrix)
{
  if (this->size != _tmatrix.size) {
    MatrixExceptionDifferentDimensions e(__LINE__, __FILE__);
    throw e;
  }
  TMatrix<ValType> result(*this);
  for (int i = 0; i < result.size; i++)
    result.elems[i] = result.elems[i] + _tmatrix.elems[i];
  return result;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& _tmatrix)
{
  if (this->size != _tmatrix.size) {
    MatrixExceptionDifferentDimensions e(__LINE__, __FILE__);
    throw e;
  }
  TMatrix<ValType> result(*this);
  for (int i = 0; i < result.size; i++)
    result.elems[i] = result.elems[i] - _tmatrix.elems[i];
  return result;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& _tmatrix)
{
  if (this->size != _tmatrix.size) {
    MatrixExceptionDifferentDimensions e(__LINE__, __FILE__);
    throw e;
  }
  TMatrix<ValType> result(this->size);
  for (int i = 0; i < this->size; i++)
    for (int j = i; j < this->size; j++)
    {
      ValType dotProduct = ValType(0);
      for (int k = i; k <= j; k++)
        dotProduct += this->elems[i][k] * _tmatrix[k][j];
      result[i][j] = dotProduct;
    }
  return result;
}

template<typename ValType>
TVector<ValType> TMatrix<ValType>::operator*(const TVector<ValType>& _tvector)
{
  int _size = _tvector.getSize();
  if (this->size != _size) {
    VectorExceptionDifferentDimensions e(__LINE__, __FILE__);
    throw e;
  }
  TVector<ValType> result(_size);
  for (int i = 0; i < _size; i++)
    result[i] = this->elems[i] * _tvector;
  return result;
}

template<typename ValType>
ValType TMatrix<ValType>::determinant()
{
  ValType result;
  result = ValType(1);
  for (int i = 0; i < this->size; i++)
    result *= this->elems[i][i];
  return result;
};

#endif // !__MATRIX_H__