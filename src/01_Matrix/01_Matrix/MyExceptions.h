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

class VectorExceptionOutOfRange : public MyException
{
public:
  VectorExceptionOutOfRange();
  VectorExceptionOutOfRange(const VectorExceptionOutOfRange& _exception);
  VectorExceptionOutOfRange(int _line, const char* _file);
  ~VectorExceptionOutOfRange();
};

class VectorExceptionDifferentDimensions : public MyException
{
public:
  VectorExceptionDifferentDimensions();
  VectorExceptionDifferentDimensions(const VectorExceptionDifferentDimensions& _exception);
  VectorExceptionDifferentDimensions(int _line, const char* _file);
  ~VectorExceptionDifferentDimensions();
};

class MatrixExceptionDifferentDimensions : public MyException
{
public:
  MatrixExceptionDifferentDimensions();
  MatrixExceptionDifferentDimensions(const MatrixExceptionDifferentDimensions& _exception);
  MatrixExceptionDifferentDimensions(int _line, const char* _file);
  ~MatrixExceptionDifferentDimensions();
};

class VectorExceptionNotPositiveDimension : public MyException
{
public:
  VectorExceptionNotPositiveDimension();
  VectorExceptionNotPositiveDimension(const VectorExceptionNotPositiveDimension& _exception);
  VectorExceptionNotPositiveDimension(int _line, const char* _file);
  ~VectorExceptionNotPositiveDimension();
};

#endif // !__MY_EXCEPTIONS_H__