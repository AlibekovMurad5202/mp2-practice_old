#include "Variables.h"

Variables::Variables(int _countOFVariables, const std::string* _variables)
{
  countOfVariables = _countOFVariables;
  values = new double[countOfVariables];
  variables = new std::string[countOfVariables];
  for (int i = 0; i < countOfVariables; i++)
  {
    variables[i] = _variables[i];
    std::cout << "Set the value of the variable: " << variables[i] << " = ";
    std::cin >> values[i];
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

Variables::~Variables()
{
  if (variables != nullptr)
    delete[] variables;
  if (values != nullptr)
    delete[] values;
}