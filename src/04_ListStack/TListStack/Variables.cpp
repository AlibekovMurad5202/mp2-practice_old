#include "Variables.h"

/*Variables::Variables(const std::string* _variables)
{
  int countOfOperands = 0;
  for (int i = 0; _variables[i] != " "; i++)
    countOfOperands++;
  countOfVariables = countOfOperands;

  values = new double[countOfVariables];
  operands = new std::string[countOfVariables];

  for (int i = 0; i < countOfVariables; i++)
  {
    operands[i] = _variables[i];

    bool cont = false;
    for (int j = 0; j < i; j++)
      if (operands[i] == operands[j]) {
        values[i] = values[j];
        cont = true;
        break;
      }
    if (cont) continue;

    if (isNumber(operands[i]))
      values[i] = stod(operands[i], 0);
    else {
      std::cout << "Set the value of the variable: " << operands[i] << " = ";
      std::cin >> values[i];
    }
  }
}*/

Variables::Variables() 
{
  countOfVariables = 0;
  operands = nullptr;
  values = nullptr;
}

void Variables::setValues()
{
  values = new double[countOfVariables];

  for (int i = 0; i < countOfVariables; i++)
  {
    bool cont = false;
    for (int j = 0; j < i; j++)
      if (operands[i] == operands[j]) {
        values[i] = values[j];
        cont = true;
        break;
      }
    if (cont) continue;

    if (isNumber(operands[i]))
      values[i] = stod(operands[i], 0);
    else {
      std::cout << "Set the value of the variable: " << operands[i] << " = ";
      std::cin >> values[i];
    }
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
  return ((!_str.empty()) && (_str.find_first_not_of("0123456789.") == _str.npos));
}

Variables::~Variables()
{
  if (operands != nullptr) delete[] operands;
  if (values != nullptr) delete[] values;
}