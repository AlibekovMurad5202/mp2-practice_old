#include "Converter.h"
#include "string"
#include "iostream"

std::string Converter::postfixForm;
int Converter::countOfOperands;
int Converter::countOfOperators;

std::string Converter::ConvertToPostfixForm(const std::string & _expression)
{
  std::string buffer;
  int lengthOfExpression = _expression.length();
  int numberOfOperators = 0;
  int numberOfOperands = 0;
  int numberOfLeftBrackets = 0;
  int numberOfRightBrackets = 0;
  char lastSymbol = 0;

  Stack<char> operators(lengthOfExpression);
  Stack<std::string> operands(lengthOfExpression);

  for (int i = 0; i < lengthOfExpression; i++)
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

    if (_expression[i] == ' ') ;
    else if ((_expression[i] != '+') && (_expression[i] != '-')
      && (_expression[i] != '*') && (_expression[i] != '/')
      && (_expression[i] != '(') && (_expression[i] != ')'))
    {
      if (numberOfOperands == numberOfOperators + 1)
      {
        ExceptionWrongExpression ex(__LINE__, __FILE__);
        throw ex;
      }

      buffer.push_back(_expression[i]);
      if (i == (lengthOfExpression - 1))
      {
        numberOfOperands++;
        operands.Push(buffer);
        buffer.clear();
      }
    }
    else if (_expression[i] == '(')
    {
      if ((lastSymbol != '+') && (lastSymbol != '-')
        && (lastSymbol != '*') && (lastSymbol != '/')
        && (lastSymbol != ' '))
      {
        ExceptionWrongExpression ex(__LINE__, __FILE__);
        throw ex;
      }
      numberOfLeftBrackets++;
      operators.Push(_expression[i]);
    }
    else if (_expression[i] == ')')
    {
      if ((lastSymbol == '+') || (lastSymbol == '-')
       || (lastSymbol == '*') || (lastSymbol == '/')
       || (lastSymbol == '(') || (lastSymbol == ')'))
      {
        ExceptionWrongExpression ex(__LINE__, __FILE__);
        throw ex;
      }
      numberOfRightBrackets++;
      while (operators.Top() != '(')
      {
        std::string tmp;
        try
        {
          tmp.push_back(operators.Top());
          operators.Pop();
          operands.Push(tmp);
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
        std::string tmp;
        tmp.push_back(operators.Top());
        operators.Pop();
        operands.Push(tmp);
      }
      operators.Push(_expression[i]);
      numberOfOperators++;
    }

    if (_expression[i] != ' ')
      lastSymbol = _expression[i];
  }

  if ((numberOfOperands != numberOfOperators + 1)
    || (numberOfLeftBrackets != numberOfRightBrackets))
  {
    ExceptionWrongExpression e(__LINE__, __FILE__);
    throw e;
  }

  while (!operators.IsEmpty())
  {
    std::string tmp;
    tmp.push_back(operators.Top());
    operators.Pop();
    operands.Push(tmp);
  }

  Stack<std::string> reverseStackOfOperands(lengthOfExpression);
  for (; !operands.IsEmpty(); operands.Pop())
    reverseStackOfOperands.Push(operands.Top());

  int startPosition = 0;
  while (!reverseStackOfOperands.IsEmpty())
  {
    startPosition = postfixForm.length();
    postfixForm.insert(startPosition, reverseStackOfOperands.Top());
    reverseStackOfOperands.Pop();
    buffer = ' ';
    postfixForm.insert(postfixForm.length(), buffer);
  }

  countOfOperators = numberOfOperators;
  countOfOperands = numberOfOperands;
  return postfixForm;
}

double Converter::Calculate(const std::string & _postfixForm, const double values[])
{
  Stack<double> result(postfixForm.length());
  std::string tmp;

  for (int i = 0, j = 0; i < postfixForm.length(); i++)
  {
    if (postfixForm[i] != ' ')
    {
      tmp.push_back(postfixForm[i]);
    }
    else
    {
      if ((tmp != "*") && (tmp != "/") && (tmp != "+") && (tmp != "-"))
      {
        if (!isNumber(tmp))
          result.Push(values[j++]);
        else
          result.Push(stod(tmp, 0));
        tmp.clear();
      }
      else if (tmp == "*")
      {
        double b = result.Top(); result.Pop();
        double a = result.Top(); result.Pop();
        result.Push(a * b);
      }
      else if (tmp == "/")
      {
        double b = result.Top(); result.Pop();
        double a = result.Top(); result.Pop();
        if (b == 0) 
        {
          ExceptionDivisionByZero e(__LINE__, __FILE__);
          throw e;
        }
        result.Push(a / b);
      }
      else if (tmp == "+")
      {
        double b = result.Top(); result.Pop();
        double a = result.Top(); result.Pop();
        result.Push(a + b);
      }
      else if (tmp == "-")
      {
        double b = result.Top(); result.Pop();
        double a = result.Top(); result.Pop();
        result.Push(a - b);
      }
    }
    tmp.clear();
  }
  return result.Top();
}

int Converter::getPriorityOfOperator(const char _operator)
{
  if ((_operator == '*') || (_operator == '/')) return 3;
  if ((_operator == '+') || (_operator == '-')) return 2;
  if (_operator == ')') return 1;
  return 0;
}

bool Converter::isNumber(const std::string& _str)
{
  return ((!_str.empty()) && (_str.find_first_not_of("0123456789") == _str.npos));
}