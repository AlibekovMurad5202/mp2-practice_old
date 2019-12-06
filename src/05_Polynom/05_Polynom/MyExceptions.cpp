#include "MyExceptions.h"

MyException::MyException()
{
  str_what = 0;
  line = 0;
  file = 0;
}

MyException::MyException(int _line, const char* _file)
{
  str_what = 0;
  line = _line;
  file = _file;
}

MyException::MyException(const MyException& _exception)
  : str_what(_exception.what()),
  line(_exception.errorLine()),
  file(_exception.errorFile()) {}

MyException::MyException(const char* message, int _line, const char* _file)
  : str_what(message),
  line(_line),
  file(_file) {}

MyException::~MyException()
{
  line = -1;
}

ExceptionWrongExpression::ExceptionWrongExpression()
{
  str_what = "Expression is wrong!";
  line = -1;
  file = 0;
}

ExceptionWrongExpression::ExceptionWrongExpression(const ExceptionWrongExpression& _exception)
{
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionWrongExpression::ExceptionWrongExpression(int _line, const char* _file)
{
  str_what = "Expression is wrong!";
  line = _line;
  file = _file;
}

ExceptionWrongExpression::~ExceptionWrongExpression()
{
  line = -1;
}

ExceptionNoNodeInList::ExceptionNoNodeInList()
{
  str_what = "There is not such node!";
  line = -1;
  file = 0;
}

ExceptionNoNodeInList::ExceptionNoNodeInList(const ExceptionNoNodeInList& _exception)
{
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionNoNodeInList::ExceptionNoNodeInList(int _line, const char* _file)
{
  str_what = "There is not such node!";
  line = _line;
  file = _file;
}

ExceptionNoNodeInList::~ExceptionNoNodeInList()
{
  line = -1;
}

ExceptionNotPositiveSize::ExceptionNotPositiveSize()
{
  str_what = "Stack has not positive size!";
  line = -1;
  file = 0;
}

ExceptionNotPositiveSize::ExceptionNotPositiveSize(const ExceptionNotPositiveSize& _exception)
{
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionNotPositiveSize::ExceptionNotPositiveSize(int _line, const char* _file)
{
  str_what = "Stack has not positive size!";
  line = _line;
  file = _file;
}

ExceptionNotPositiveSize::~ExceptionNotPositiveSize()
{
  line = -1;
}

ExceptionFullStack::ExceptionFullStack()
{
  str_what = "Stack is full!";
  line = -1;
  file = 0;
}

ExceptionFullStack::ExceptionFullStack(const ExceptionFullStack& _exception)
{
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionFullStack::ExceptionFullStack(int _line, const char* _file)
{
  str_what = "Stack is full!";
  line = _line;
  file = _file;
}

ExceptionFullStack::~ExceptionFullStack()
{
  line = -1;
}

ExceptionListIsEnded::ExceptionListIsEnded()
{
  str_what = "List is ended!";
  line = -1;
  file = 0;
}

ExceptionListIsEnded::ExceptionListIsEnded(const ExceptionListIsEnded& _exception)
{
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionListIsEnded::ExceptionListIsEnded(int _line, const char* _file)
{
  str_what = "List is ended!";
  line = _line;
  file = _file;
}

ExceptionListIsEnded::~ExceptionListIsEnded()
{
  line = -1;
}

ExceptionEmptyStack::ExceptionEmptyStack()
{
  str_what = "Stack is empty!";
  line = -1;
  file = 0;
}

ExceptionEmptyStack::ExceptionEmptyStack(const ExceptionEmptyStack& _exception)
{
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionEmptyStack::ExceptionEmptyStack(int _line, const char* _file)
{
  str_what = "Stack is empty!";
  line = _line;
  file = _file;
}

ExceptionEmptyStack::~ExceptionEmptyStack()
{
  line = -1;
}


ExceptionEmptyList::ExceptionEmptyList()
{
  str_what = "List is empty!";
  line = -1;
  file = 0;
}

ExceptionEmptyList::ExceptionEmptyList(const ExceptionEmptyList& _exception)
{
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionEmptyList::ExceptionEmptyList(int _line, const char* _file)
{
  str_what = "List is empty!";
  line = _line;
  file = _file;
}

ExceptionEmptyList::~ExceptionEmptyList()
{
  line = -1;
}


ExceptionDivisionByZero::ExceptionDivisionByZero()
{
  str_what = "Division by zero!";
  line = -1;
  file = 0;
}

ExceptionDivisionByZero::ExceptionDivisionByZero(const ExceptionDivisionByZero& _exception)
{
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionDivisionByZero::ExceptionDivisionByZero(int _line, const char* _file)
{
  str_what = "Division by zero!";
  line = _line;
  file = _file;
}

ExceptionDivisionByZero::~ExceptionDivisionByZero()
{
  line = -1;
};