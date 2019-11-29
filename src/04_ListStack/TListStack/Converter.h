#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "stdlib.h"
#include "TArrayStack.h"
#include "TListStack.h"
#include "Variables.h"

class Converter
{
private:
  TStack<char>* operators;
  TStack<std::string>* stackOfOperands;
  TStack<double>* result;

  int getPriorityOfOperator(const char _operator);

public:
  std::string *operands;
  std::string postfixForm;

  explicit Converter(bool _isTListStack = false);
  ~Converter();

  std::string ConvertToPostfixForm(const std::string& _expression);
  double Calculate(const std::string& _postfixForm, const Variables & _var);
};

#endif // !__CONVERTER_H__