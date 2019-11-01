#include "Converter.h"
#include "string"
#include "iostream"

std::string Converter::postfixForm;
int Converter::countOfOperands;
std::string *Converter::operands;
//int Converter::countOfOperators;

std::string Converter::ConvertToPostfixForm(const std::string & _expression)
{
  std::string *_operands = new std::string[_expression.length()];
  std::string buffer;
  int lengthOfExpression = _expression.length();
  int numberOfOperators = 0;
  int numberOfOperands = 0;
  countOfOperands = 0;
  int numberOfLeftBrackets = 0;
  int numberOfRightBrackets = 0;
  char lastSymbol = 0;
  postfixForm.clear();
  int indexOfOperand = 0;

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
        {
          int k = 0;
          while ((k < indexOfOperand) &&
            (_operands[k++] != _operands[indexOfOperand])) {};
          if (k == indexOfOperand)
            _operands[indexOfOperand++] = buffer;
        }
        buffer.clear();
      }
    }

    if (_expression[i] == ' ') ;
    else if ((_expression[i] != '+') && (_expression[i] != '-')
      && (_expression[i] != '*') && (_expression[i] != '/')
      && (_expression[i] != '(') && (_expression[i] != ')'))
    {
      if (numberOfOperands == (numberOfOperators + 1))
      {
        ExceptionWrongExpression ex(__LINE__, __FILE__);
        throw ex;
      }

      buffer.push_back(_expression[i]);
      if (i == (lengthOfExpression - 1))
      {
        numberOfOperands++;
        operands.Push(buffer);
        {
          int k = 0;
          while ((k < indexOfOperand) &&
            (_operands[k++] != _operands[indexOfOperand])) {
          };
          if (k == indexOfOperand)
            _operands[indexOfOperand++] = buffer;
        }
        buffer.clear();
      }
    }
    else if (_expression[i] == '(')
    {
      if ((lastSymbol != '+') && (lastSymbol != '-')
        && (lastSymbol != '*') && (lastSymbol != '/')
        && (lastSymbol != ' ') && (lastSymbol != '(')
        && (lastSymbol != 0))
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
       || (lastSymbol == '('))// || (lastSymbol == ')'))
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
      if (lastSymbol == 0)
      {
        ExceptionWrongExpression ex(__LINE__, __FILE__);
        throw ex;
      }
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

  countOfOperands = numberOfOperands;
  {
    Converter::operands = new std::string[countOfOperands];
    for (int i = 0; i < countOfOperands; i++)
      Converter::operands[i] = _operands[i];
    delete[] _operands;
  }

  return postfixForm;
}

double Converter::Calculate(const std::string & _postfixForm, const Variables& _var)
{
  Stack<double> result(postfixForm.length());
  std::string tmp;
  int value;
  for (int i = 0, j = 0; i < postfixForm.length(); i++)
  {
    if ((postfixForm[i] != ' ')) 
    {
      tmp.push_back(postfixForm[i]);
    }
    else
    {
      if ((tmp != "*") && (tmp != "/") && (tmp != "+") && (tmp != "-"))
      {
        int idx = 0;
        while ((idx < _var.countOfVariables) && (operands[idx++] != tmp));
        idx--;
        result.Push(_var.values[idx]);
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

void Converter::Clear()
{
  Converter::countOfOperands = 0;
  Converter::postfixForm.clear();
  delete[] operands;
}

std::string* Converter::getOperands()
{
  return operands;
}

int Converter::getCountOfOperands()
{
  return countOfOperands;
}