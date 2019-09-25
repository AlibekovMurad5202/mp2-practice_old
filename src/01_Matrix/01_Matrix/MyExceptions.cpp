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

MyException::MyException(const char* error, const char* reason, int _line, const char* _file)
  : str_what(error),
  str_why(reason),
  line(_line),
  file(_file) {}

MyException::MyException(const char* message, int _line, const char* _file)
  : str_what(message),
  line(_line),
  file(_file) {}

MyException::~MyException()
{
  line = -1;
}

ExceptionOutOfRange::ExceptionOutOfRange()
{
  str_what = "Value out of bounds!";
  str_why = "Value does not match conditions.";
  line = -1;
  file = 0;
}

ExceptionOutOfRange::ExceptionOutOfRange(const ExceptionOutOfRange& _exception)
{
  str_why = _exception.why();
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionOutOfRange::ExceptionOutOfRange(int _line, const char* _file)
{
  str_what = "Value out of bounds!";
  str_why = "Value does not match conditions.";
  line = _line;
  file = _file;
}

ExceptionOutOfRange::~ExceptionOutOfRange()
{
  line = -1;
}

ExceptionFullContainer::ExceptionFullContainer()
{
  str_what = "Cannot add item!";
  str_why = "Container is full.";
  line = -1;
  file = 0;
}

ExceptionFullContainer::ExceptionFullContainer(const ExceptionFullContainer& _exception)
{
  str_why = _exception.why();
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionFullContainer::ExceptionFullContainer(int _line, const char* _file)
{
  str_what = "Cannot add item!";
  str_why = "Container is full.";
  line = _line;
  file = _file;
}

ExceptionFullContainer::~ExceptionFullContainer()
{
  line = -1;
}

ExceptionEmptyContainer::ExceptionEmptyContainer()
{
  str_what = "Cannot delete item!";
  str_why = "Container is empty.";
  line = -1;
  file = 0;
}

ExceptionEmptyContainer::ExceptionEmptyContainer(const ExceptionEmptyContainer& _exception)
{
  str_why = _exception.why();
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionEmptyContainer::ExceptionEmptyContainer(int _line, const char* _file)
{
  str_what = "Cannot delete item!";
  str_why = "Container is empty.";
  line = _line;
  file = _file;
}

ExceptionEmptyContainer::~ExceptionEmptyContainer()
{
  line = -1;
}

ExceptionItemNotFound::ExceptionItemNotFound()
{
  str_what = "Item not found!";
  str_why = "The item is not in container.";
  line = -1;
  file = 0;
}

ExceptionItemNotFound::ExceptionItemNotFound(const ExceptionItemNotFound& _exception)
{
  str_why = _exception.why();
  str_what = _exception.what();
  line = _exception.errorLine();
  file = _exception.errorFile();
}

ExceptionItemNotFound::ExceptionItemNotFound(int _line, const char* _file)
{
  str_what = "Item not found!";
  str_why = "The item is not in container.";
  line = _line;
  file = _file;
}

ExceptionItemNotFound::~ExceptionItemNotFound()
{
  line = -1;
};