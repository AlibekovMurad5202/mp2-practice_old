#ifndef __MY_EXCEPTIONS_H__
#define __MY_EXCEPTIONS_H__

#include <exception>

class MyException : public std::exception
{
protected:
  char s_e[20] = "Unknown exception!";
  const char* str_what;
  int line;
  const char* file;

public:
  MyException();
  MyException(int _line, const char* _file);
  MyException(const MyException& _exception);
  MyException(const char* message, int _line, const char* _file);
  ~MyException();

  virtual const char* what() const { return str_what ? str_what : s_e; }
  virtual int errorLine() const { return line; }
  virtual const char* errorFile() const { return file; }
};

class ExceptionWrongExpression : public MyException
{
public:
  ExceptionWrongExpression();
  ExceptionWrongExpression(const ExceptionWrongExpression& _exception);
  ExceptionWrongExpression(int _line, const char* _file);
  ~ExceptionWrongExpression();
};

class ExceptionDifferentDegrees : public MyException
{
public:
  ExceptionDifferentDegrees();
  ExceptionDifferentDegrees(const ExceptionDifferentDegrees& _exception);
  ExceptionDifferentDegrees(int _line, const char* _file);
  ~ExceptionDifferentDegrees();
};

class ExceptionMonomDoesNotExist : public MyException
{
public:
  ExceptionMonomDoesNotExist();
  ExceptionMonomDoesNotExist(const ExceptionMonomDoesNotExist& _exception);
  ExceptionMonomDoesNotExist(int _line, const char* _file);
  ~ExceptionMonomDoesNotExist();
};

class ExceptionNotPositiveSize : public MyException
{
public:
  ExceptionNotPositiveSize();
  ExceptionNotPositiveSize(const ExceptionNotPositiveSize& _exception);
  ExceptionNotPositiveSize(int _line, const char* _file);
  ~ExceptionNotPositiveSize();
};

class ExceptionNoNodeInList : public MyException
{
public:
  ExceptionNoNodeInList();
  ExceptionNoNodeInList(const ExceptionNoNodeInList& _exception);
  ExceptionNoNodeInList(int _line, const char* _file);
  ~ExceptionNoNodeInList();
};

class ExceptionListIsEnded : public MyException
{
public:
  ExceptionListIsEnded();
  ExceptionListIsEnded(const ExceptionListIsEnded& _exception);
  ExceptionListIsEnded(int _line, const char* _file);
  ~ExceptionListIsEnded();
};

class ExceptionFullStack : public MyException
{
public:
  ExceptionFullStack();
  ExceptionFullStack(const ExceptionFullStack& _exception);
  ExceptionFullStack(int _line, const char* _file);
  ~ExceptionFullStack();
};

class ExceptionEmptyStack : public MyException
{
public:
  ExceptionEmptyStack();
  ExceptionEmptyStack(const ExceptionEmptyStack& _exception);
  ExceptionEmptyStack(int _line, const char* _file);
  ~ExceptionEmptyStack();
};

class ExceptionEmptyList : public MyException
{
public:
  ExceptionEmptyList();
  ExceptionEmptyList(const ExceptionEmptyList& _exception);
  ExceptionEmptyList(int _line, const char* _file);
  ~ExceptionEmptyList();
};

class ExceptionDivisionByZero : public MyException
{
public:
  ExceptionDivisionByZero();
  ExceptionDivisionByZero(const ExceptionDivisionByZero& _exception);
  ExceptionDivisionByZero(int _line, const char* _file);
  ~ExceptionDivisionByZero();
};

#endif // !__MY_EXCEPTIONS_H__