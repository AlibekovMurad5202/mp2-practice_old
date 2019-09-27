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

VectorExceptionOutOfRange::VectorExceptionOutOfRange()
{
  str_what = "Index out of bounds!";
  line = -1;
  file = 0;
}

VectorExceptionOutOfRange::VectorExceptionOutOfRange(const VectorExceptionOutOfRange& _exception)
{
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

VectorExceptionOutOfRange::VectorExceptionOutOfRange(int _line, const char* _file)
{
  str_what = "Index out of bounds!";
  line = _line;
  file = _file;
}

VectorExceptionOutOfRange::~VectorExceptionOutOfRange()
{
  line = -1;
}

VectorExceptionDifferentDimensions::VectorExceptionDifferentDimensions()
{
  str_what = "Vectors have different dimensions!"; 
  line = -1; 
  file = 0;
}

VectorExceptionDifferentDimensions::VectorExceptionDifferentDimensions(const VectorExceptionDifferentDimensions& _exception)
{
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

VectorExceptionDifferentDimensions::VectorExceptionDifferentDimensions(int _line, const char* _file)
{
  str_what = "Vectors have different dimensions!"; 
  line = _line; 
  file = _file;
}

VectorExceptionDifferentDimensions::~VectorExceptionDifferentDimensions()
{
  line = -1;
}

MatrixExceptionDifferentDimensions::MatrixExceptionDifferentDimensions()
{
  str_what = "Matrices have different dimensions!";
  line = -1;
  file = 0;
}

MatrixExceptionDifferentDimensions::MatrixExceptionDifferentDimensions(const MatrixExceptionDifferentDimensions& _exception)
{
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

MatrixExceptionDifferentDimensions::MatrixExceptionDifferentDimensions(int _line, const char* _file)
{
  str_what = "Matrices have different dimensions!";
  line = _line;
  file = _file;
}

MatrixExceptionDifferentDimensions::~MatrixExceptionDifferentDimensions()
{
  line = -1;
};