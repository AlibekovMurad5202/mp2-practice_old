#include "Converter.h"
#define TARRAYSTACK_MAX_SIZE 1024

std::string Converter::GetPostfixForm() const
{
  return postfixForm;
}

void Converter::setVariables()
{
  variables.setValues();
}

std::string Converter::ConvertToPostfixForm(const std::string & _expression)
{
  std::string *_operands = new std::string[_expression.length()];
  std::string buffer;
  int lengthOfExpression = _expression.length();
  int countOfOperators = 0;
  int countOfOperands = 0;
  int countOfLeftBrackets = 0;
  int countOfRightBrackets = 0;
  char lastSymbol = 0;
  int indexOfOperand = 0;

  for (int i = 0; i < lengthOfExpression; i++)
  {
    if (buffer.length() != 0)
    {
      if ((_expression[i] == '+') || (_expression[i] == '-')
        || (_expression[i] == '*') || (_expression[i] == '/')
        || (_expression[i] == '(') || (_expression[i] == ')')
        || (_expression[i] == ' '))
      {
        variables.countOfVariables++;
        countOfOperands++;
        stackOfOperands->Push(buffer);
        {
          int k = 0;
          while ((k < indexOfOperand) && (_operands[k++] != _operands[indexOfOperand])) {};
          if (k == indexOfOperand) _operands[indexOfOperand++] = buffer;
        }
        buffer.clear();
      }
    }

    if (_expression[i] == ' ');
    else if ((_expression[i] != '+') && (_expression[i] != '-')
      && (_expression[i] != '*') && (_expression[i] != '/')
      && (_expression[i] != '(') && (_expression[i] != ')'))
    {
      if (countOfOperands == countOfOperators + 1)
        throw ExceptionWrongExpression(__LINE__, __FILE__);

      buffer.push_back(_expression[i]);
      if (i == lengthOfExpression - 1)
      {
        countOfOperands++;
        stackOfOperands->Push(buffer);
        {
          int k = 0;
          while ((k < indexOfOperand) && (_operands[k++] != _operands[indexOfOperand])) {};
          if (k == indexOfOperand) _operands[indexOfOperand++] = buffer;
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
        throw ExceptionWrongExpression(__LINE__, __FILE__);
      countOfLeftBrackets++;
      operators->Push(_expression[i]);
    }
    else if (_expression[i] == ')')
    {
      if ((lastSymbol == '+') || (lastSymbol == '-')
        || (lastSymbol == '*') || (lastSymbol == '/')
        || (lastSymbol == '('))
        throw ExceptionWrongExpression(__LINE__, __FILE__);
      countOfRightBrackets++;
      while (operators->Top() != '(')
      {
        std::string tmp;
        try
        {
          tmp.push_back(operators->Top());
          operators->Pop();
          stackOfOperands->Push(tmp);
        }
        catch (ExceptionEmptyStack const&)
        {
          throw ExceptionWrongExpression(__LINE__, __FILE__);
        }
      }
      operators->Pop();
    }
    else if (operators->IsEmpty())
    {
      if (lastSymbol == 0)
        throw ExceptionWrongExpression(__LINE__, __FILE__);
      operators->Push(_expression[i]);
      countOfOperators++;
    }
    else if (getPriorityOfOperator(_expression[i]) > getPriorityOfOperator(operators->Top()))
    {
      operators->Push(_expression[i]);
      countOfOperators++;
    }
    else
    {
      while ((!operators->IsEmpty()) && (operators->Top() != '(')
        && (getPriorityOfOperator(_expression[i]) <= getPriorityOfOperator(operators->Top())))
      {
        std::string tmp;
        tmp.push_back(operators->Top());
        operators->Pop();
        stackOfOperands->Push(tmp);
      }
      operators->Push(_expression[i]);
      countOfOperators++;
    }

    if (_expression[i] != ' ')
      lastSymbol = _expression[i];
  }

  if ((countOfOperands != countOfOperators + 1)
    || (countOfLeftBrackets != countOfRightBrackets))
    throw ExceptionWrongExpression(__LINE__, __FILE__);

  while (!operators->IsEmpty())
  {
    std::string tmp;
    tmp.push_back(operators->Top());
    operators->Pop();
    stackOfOperands->Push(tmp);
  }

  TArrayStack<std::string> reverseStackOfOperands(lengthOfExpression);
  for (; !stackOfOperands->IsEmpty(); stackOfOperands->Pop())
    reverseStackOfOperands.Push(stackOfOperands->Top());

  int startPosition = 0;

  while (!reverseStackOfOperands.IsEmpty())
  {
    startPosition = postfixForm.length();
    postfixForm.insert(startPosition, reverseStackOfOperands.Top());
    reverseStackOfOperands.Pop();
    buffer = ' ';
    postfixForm.insert(postfixForm.length(), buffer);
  }

  variables.countOfVariables = countOfOperands;
  variables.operands = new std::string[countOfOperands];
  for (int i = 0; i < countOfOperands; i++)
    variables.operands[i] = _operands[i];
  delete[] _operands;
  
  return postfixForm;
}

double Converter::Calculate()
{
  std::string tmp;
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
        while ((idx < variables.countOfVariables) && (variables.operands[idx++] != tmp));
        idx--;
        result->Push(variables.values[idx]);
      }
      else if (tmp == "*")
      {
        double b = result->Top(); result->Pop();
        double a = result->Top(); result->Pop();
        result->Push(a * b);
      }
      else if (tmp == "/")
      {
        double b = result->Top(); result->Pop();
        double a = result->Top(); result->Pop();
        if (b == 0) throw ExceptionDivisionByZero(__LINE__, __FILE__);
        result->Push(a / b);
      }
      else if (tmp == "+")
      {
        double b = result->Top(); result->Pop();
        double a = result->Top(); result->Pop();
        result->Push(a + b);
      }
      else if (tmp == "-")
      {
        double b = result->Top(); result->Pop();
        double a = result->Top(); result->Pop();
        result->Push(a - b);
      }
      tmp.clear();
    }
  }
  return result->Top();
}

int Converter::getPriorityOfOperator(const char _operator)
{
  if ((_operator == '*') || (_operator == '/')) return 3;
  if ((_operator == '+') || (_operator == '-')) return 2;
  if (_operator == ')') return 1;
  return 0;
}

Converter::Converter(bool _isTListStack)
{
  if (_isTListStack == true)
  {
    operators = new TListStack<char>();
    stackOfOperands = new TListStack<std::string>();
    result = new TListStack<double>();
  }
  else
  {
    operators = new TArrayStack<char>(TARRAYSTACK_MAX_SIZE);
    stackOfOperands = new TArrayStack<std::string>(TARRAYSTACK_MAX_SIZE);
    result = new TArrayStack<double>(TARRAYSTACK_MAX_SIZE);
  }
}

Converter::~Converter()
{
  delete stackOfOperands;
  delete operators;
  delete result;
}