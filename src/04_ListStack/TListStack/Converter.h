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

  std::string postfixForm;
  Variables variables;

  int getPriorityOfOperator(const char _operator);

public:
  explicit Converter(bool _isTListStack = false);
  ~Converter();

  std::string GetPostfixForm() const;
  void setVariables();

  std::string ConvertToPostfixForm(const std::string& _expression);
  double Calculate();
};

#endif // !__CONVERTER_H__