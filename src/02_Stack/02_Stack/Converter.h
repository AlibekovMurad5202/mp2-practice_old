#ifndef __CONVERTER__H__
#define __CONVERTER__H__

#include "string"
#include "stdlib.h"
#include "Stack.h"

static class Converter
{
private:
  static int countOfOperands;
  static int countOfOperators;
  static std::string postfixForm;
  //static Stack<char> operators;
  //static Stack<std::string> operands;

public:
  static std::string ConvertToPostfixForm(const std::string& _expression);
  static double Calculate(const std::string& _postfixForm, const double values[]);
  static int getPriorityOfOperator(const char _operator);

private:
  static bool isNumber(const std::string& _str);
};

#endif // !__CONVERTER__H__