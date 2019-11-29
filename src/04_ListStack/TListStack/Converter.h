#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "stdlib.h"
#include "TArrayStack.h"
#include "TListStack.h"
#include "Stack.h"
#include "Variables.h"

class Converter
{
public:
  std::string *operands;
  std::string postfixForm;

private:
  int getPriorityOfOperator(const char _operator);
  Stack<char>* operators;
  Stack<std::string>* stackOfOperands;
  Stack<double>* result;

public:
  explicit Converter(bool _isTListStack = false);
  ~Converter();

  std::string ConvertToPostfixForm(const std::string& _expression);
  double Calculate(const std::string& _postfixForm, const Variables & _var);
};

#endif // !__CONVERTER_H__