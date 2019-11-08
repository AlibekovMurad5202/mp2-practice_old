#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#include "iostream"
#include "string"

class Variables
{
public:
  int countOfVariables;
  std::string* variables;
  double* values;

  Variables(const std::string* _variables);

  void setValues();
  double& operator[](int index);
  const double& operator[](int index) const;

  ~Variables();

private:
  static bool isNumber(const std::string& _str);
};


#endif // !__VARIABLES_H__