#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "stdlib.h"
#include "Stack.h"
#include "Variables.h"

static class Converter
{
private:
  static std::string postfixForm;
  static int getPriorityOfOperator(const char _operator);

public:
  static std::string ConvertToPostfixForm(const std::string& _expression);
  static double Calculate(const std::string& _postfixForm, const Variables & _var);
  static void Clear();

  static std::string *operands;
};

#endif // !__CONVERTER_H__