#ifndef __TVECTOR_H__
#define __TVECTOR_H__

template<typename ValType>
class TVector
{
    protected:
        int size;
        int startIndex;
        ValType* elems;

    public:
        TVector(int _size = 10, int _startIndex = 0);
        TVector(const TVector& _tvector);
        ~TVector();
        
        int getSize() const;
        int getStartIndex() const;

        ValType Length() const;

        bool operator== (const TVector& _tvector) const;
        bool operator!= (const TVector& _tvector) const;
        TVector operator+ (ValType _value);
        TVector operator- (ValType _value);
        TVector operator* (ValType _value);
        TVector operator+ (const TVector& _tvector);
        Tvector operator- (const Tvector& _tvector);
        ValType operator* (const TVector& _tvector);
        TVector& operator= (const TVector& _tvector);
        ValType& operator[] (int index);
        friend std::ostream& operator<< (std::ostream& os, const TVector& _tvector);
        friend std::istream& operator>> (std::istream& is, TVector& _tvector);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template<typename ValType>
TVector<ValType>::TVector(int _size = 10, int _startIndex = 0)
{
    size = _size;
    startIndex = startIndex;
    elems = new ValType[size];
}

template<typename ValType>
TVector<ValType>::TVector(const TVector<ValType>& _tvector)
{
    if (this == &_tvector)
        return;
    size = _tvector.getSize();
    startIndex = _tvector.getStartIndex();
    elems = new ValType[size];
    for (int i = 0; i < size; i++)
        elems[i] = _tvector[i];
}

template<typename ValType>
TVector<ValType>::~TVector()
{
    delete[] elems;
}

template<typename ValType>
int TVector<ValType>::getSize() const
{
    return size;
}

template<typename ValType>
int TVector<ValType>::getStartIndex() const
{
    return startIndex;
}

template<typename ValType>
bool TVector<ValType>::operator== (const TVector<ValType>& _tvector) const
{
    if (_tvector.getSize() != size)
        return false;
    for (int i = 0; i < size; i++)
        if (_tvector[i] != elems[i])
            return false;
    return true;
}

template<typename ValType>
bool TVector<ValType>::operator!= (const TVector<ValType>& _tvector) const
{
    return !(*this == _tvector);
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+ (Valtype _value)
{
    TVector<Valtype> tmp(*this);
    for (int i = 0; i < size; i++)
        tmp[i] += _value;
    return tmp;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator- (Valtype _value)
{
    TVector<Valtype> tmp(*this);
    for (int i = 0; i < size; i++)
        tmp[i] -= _value;
    return tmp;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator* (Valtype _value)
{
    TVector<Valtype> tmp(*this);
    for (int i = 0; i < size; i++)
        tmp[i] *= _value;
    return tmp;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+ (const TVector<ValType>& _tvector) const
{
    if (size != _tvector.getSize())
        ; // exception

    TVector<Valtype> tmp(*this);
    for (int i = 0; i < size; i++)
        tmp[i] += _tvector[i];
    return tmp;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator- (const TVector<ValType>& _tvector) const
{
    if (size != _tvector.getSize())
        ; // exception

    TVector<Valtype> tmp(*this);
    for (int i = 0; i < size; i++)
        tmp[i] -= _tvector[i];
    return tmp;
}

template<typename ValType>
ValType TVector<ValType>::operator* (const TVector<ValType>& _tvector) const
{
    if (size != _tvector.getSize())
        ; // exception
    ValType scalarProduct = 0;
    for (int i = 0; i < size; i++)
        scalarProduct += elems[i] * _tvector[i];
    return scalarProduct;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator= (const TVector<ValType>& _tvector)
{
    if (this == &_tvector)
        return *this;
    delete[] elems;
    size = _tvector.getsize();
    elems = new ValType[size];
    for (int i = 0; i < size; i++)
        elems[i] = _tvector[i];
    return *this;
}

template<typename ValType>
ValType& TVector<ValType>::operator[] (const TVector<ValType>& _tvector)
{

}

#endif