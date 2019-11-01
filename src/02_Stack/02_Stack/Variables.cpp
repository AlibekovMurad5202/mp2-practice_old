#include "Variables.h"

Variables::Variables(int _countOFVariables, const std::string* _variables)
{
  countOfVariables = _countOFVariables;
  values = new double[countOfVariables];
  variables = new std::string[countOfVariables];

  for (int i = 0; i < countOfVariables; i++)
  { 
    variables[i] = _variables[i];

    bool cont = false;
    for (int j = 0; j < i; j++)
      if (variables[i] == variables[j]) {
        variables[j] = variables[i];
        cont = true;
        break;
      }
    if (cont) continue;

    if(isNumber(variables[i]))
      values[i] = stod(variables[i], 0);
    else {
      std::cout << "Set the value of the variable: " << variables[i] << " = ";
      std::cin >> values[i];
    }
  }
}

void Variables::setValues()
{
  for (int i = 0; i < countOfVariables; i++)
  {
    std::cout << "Set the value of the variable: " << variables[i] << " = ";
    std::cin >> values[i];
  }
}

double & Variables::operator[](int index)
{
  return values[index];
}

const double & Variables::operator[](int index) const
{
  return values[index];
}

bool Variables::isNumber(const std::string& _str)
{
  return ((!_str.empty()) && (_str.find_first_not_of("0123456789") == _str.npos));
}

Variables::~Variables()
{
  if (variables != nullptr)
    delete[] variables;
  if (values != nullptr)
    delete[] values;
}
