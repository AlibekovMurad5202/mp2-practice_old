#include "Converter.h"

std::string Coverter::ConvertToPostfixForm(const std::string & _expression)
{
  std::string buffer;
  int numberOfOperators = 0;
  int numberOfOperands = 0;
  int numberOfLeftBrackets = 0;
  int numberOfRightBrackets = 0;

  for (int i = 0; i < _expression.size(); i++)
  {
    if (buffer.length() != 0)
    {
      if ((_expression[i] == '+') || (_expression[i] == '-') 
       || (_expression[i] == '*') || (_expression[i] == '/') 
       || (_expression[i] == '(') || (_expression[i] == ')') 
       || (_expression[i] == ' '))
      {
        numberOfOperands++;
        operands.Push(buffer);
        buffer.clear();
      }
    }

    if (_expression[i] == ' ');
    else if ((_expression[i] != '+') && (_expression[i] != '-') 
      && (_expression[i] != '*') && (_expression[i] != '/') 
      && (_expression[i] != '(') && (_expression[i] != ')'))
    {
      buffer.push_back(_expression[i]);
    }
    else if (_expression[i] == '(')
    {
      numberOfLeftBrackets++;
      operators.Push(_expression[i]);
    }
    else if (_expression[i] == ')')
    {
      numberOfRightBrackets++;
      while (operators.Top() != '(')
      {
        std::string temp;
        try
        {
          temp.push_back(operators.Pop());
          operands.Push(temp);
        }
        catch (ExceptionEmptyStack const& e)
        {
          ExceptionWrongExpression ex(__LINE__, __FILE__);
          throw ex;
        }
      }
      operators.Pop();
    }
    else if (operators.IsEmpty())
    {
      operators.Push(_expression[i]);
      numberOfOperators++;
    }
    else if (getPriorityOfOperator(_expression[i]) > getPriorityOfOperator(operators.Top()))
    {
      operators.Push(_expression[i]);
      numberOfOperators++;
    }
    else
    {
      while ((!operators.IsEmpty()) && (operators.Top() != '(') 
        && (getPriorityOfOperator(_expression[i]) <= getPriorityOfOperator(operators.Top())))
      {
        std::string temp;
        temp.push_back(operators.Pop());
        operands.Push(temp);
      }
      operators.Push(_expression[i]);
      numberOfOperators++;
    }
  }

  if (buffer.length() != 0)
  {
    operands.Push(buffer);
    buffer.clear();
    numberOfOperands++;
  }

  if ((numberOfOperands != numberOfOperators + 1)
    || (numberOfLeftBrackets != numberOfRightBrackets))
  {
    ExceptionWrongExpression e(__LINE__, __FILE__);
    throw e;
  }

  while (!operators.IsEmpty())
  {
    std::string temp;
    temp.push_back(operators.Pop());
    operands.Push(temp);
  }

  std::string postfixForm;
  int startPosition = 0;
  while (!operands.IsEmpty())
  {
    startPosition = postfixForm.length();
    postfixForm.insert(startPosition, operands.Pop());
  }

  return postfixForm;
}

double Coverter::Calculate(const std::string & _postfixForm, const double values[])
{
  Stack<double> result(postfixForm.length());
  std::string temp;
  int j = 0;

  for (int i = 0; i < postfixForm.size(); i++)
  {
    if (postfixForm[i] != ' ')
    {
      temp.push_back(postfixForm[i]);
    }
    else
    {
      if ((temp != "*") && (temp != "/") && (temp != "+") && (temp != "-"))
      {
        result.Push(values[j++]);
      }
      else if (temp == "*")
      {
        double b = result.Pop();
        double a = result.Pop();
        result.Push(a * b);
      }
      else if (temp == "/")
      {
        double b = result.Pop();
        double a = result.Pop();
        if (b == 0) 
        {
          ExceptionDivisionByZero e(__LINE__, __FILE__);
          throw e;
        }
        result.Push(a / b);
      }
      else if (temp == "+")
      {
        double b = result.Pop();
        double a = result.Pop();
        result.Push(a + b);
      }
      else if (temp == "-")
      {
        double b = result.Pop();
        double a = result.Pop();
        result.Push(a - b);
      }
      temp.clear();
    }
  }
  return result.Top();
}

int Coverter::getPriorityOfOperator(const char _operator) const 
{
  if ((_operator == '*') || (_operator == '/')) return 3;
  if ((_operator == '+') || (_operator == '-')) return 2;
  if (_operator == ')') return 1;
  return 0;
}
