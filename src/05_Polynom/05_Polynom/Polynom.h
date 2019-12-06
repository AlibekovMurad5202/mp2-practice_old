#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include "TList.h"

#define MAX_KEY 999
#define UINT unsigned int

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
  Polynom operator+(const TNode<UINT, double>& _monom) const;

  Polynom operator-(const Polynom& _polynom) const;
  Polynom operator-(const TNode<UINT, double>& _monom) const;

  Polynom operator*(const Polynom& _polynom) const;
  Polynom operator*(const TNode<UINT, double>& _monom) const;

  //friend std::ostream& operator<<(std::ostream& out, const Polynom& _polynom);
  //friend std::istream& operator>>(std::istream& in, Polynom& _polynom);
};

#endif // !__POLYNOM_H__