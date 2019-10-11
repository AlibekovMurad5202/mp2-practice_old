#ifndef __CONVERTER__H__
#define __CONVERTER__H__

#include "string"
#include "stdlib.h"
#include "Stack.h"

static class Coverter
{
protected:
  Stack<char> operators;          //first stack
  Stack<std::string> operands;    //second stack
  std::string postfixForm;

public:
  std::string ConvertToPostfixForm(const std::string& _expression);
  double Calculate(const std::string& _postfixForm, const double values[]);
  int getPriorityOfOperator(const char _operator) const;
};

#endif // !__CONVERTER__H__