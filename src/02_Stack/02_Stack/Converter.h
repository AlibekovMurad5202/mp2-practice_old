#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include "string"
#include "stdlib.h"
#include "Stack.h"
#include "Variables.h"
#include "iostream"

static class Converter
{
private:
  static int countOfOperands;
  static std::string *operands;
  //static int countOfOperators;
  static std::string postfixForm;
  //static Stack<char> operators;
  //static Stack<std::string> operands;

public:
  static std::string ConvertToPostfixForm(const std::string& _expression);
  static double Calculate(const std::string& _postfixForm, const Variables & _var);
  static int getPriorityOfOperator(const char _operator);
  static void Clear();

  static std::string* getOperands();
  static int getCountOfOperands();

private:
  static bool isNumber(const std::string& _str);
};

#endif // !__CONVERTER_H__