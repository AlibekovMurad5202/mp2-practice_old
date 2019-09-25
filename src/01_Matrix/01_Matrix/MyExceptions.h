#ifndef __MY_EXCEPTIONS_H__
#define __MY_EXCEPTIONS_H__

#include <exception>

class MyException : public std::exception
{
protected:
  char s_e[20] = "Unknown exception!";
  char s_r[20] = "Unknown reason!";
  const char* str_what;
  const char* str_why;
  int line;
  const char* file;

public:
  MyException();
  MyException(int _line, const char* _file);
  MyException(const MyException& _exception);
  MyException(const char* error, const char* reason, int _line, const char* _file);
  MyException(const char* message, int _line, const char* _file);
  ~MyException();

  virtual const char* why() const { return str_why ? str_why : s_r; }
  virtual const char* what() const { return str_what ? str_what : s_e; }
  virtual int errorLine() const { return line; }
  virtual const char* errorFile() const { return file; }
};

class ExceptionOutOfRange : public MyException
{
public:
  ExceptionOutOfRange();
  ExceptionOutOfRange(const ExceptionOutOfRange& _exception);
  ExceptionOutOfRange(int _line, const char* _file);
  ~ExceptionOutOfRange();
};

class ExceptionFullContainer : public MyException
{
public:
  ExceptionFullContainer();
  ExceptionFullContainer(const ExceptionFullContainer& _exception);
  ExceptionFullContainer(int _line, const char* _file);
  ~ExceptionFullContainer();
};

class ExceptionEmptyContainer : public MyException
{
public:
  ExceptionEmptyContainer();
  ExceptionEmptyContainer(const ExceptionEmptyContainer& _exception);
  ExceptionEmptyContainer(int _line, const char* _file);
  ~ExceptionEmptyContainer();
};

class ExceptionItemNotFound : public MyException
{
public:
  ExceptionItemNotFound();
  ExceptionItemNotFound(const ExceptionItemNotFound& _exception);
  ExceptionItemNotFound(int _line, const char* _file);
  ~ExceptionItemNotFound();
};

#endif // !__MY_EXCEPTIONS_H__