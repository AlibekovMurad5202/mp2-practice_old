#include "iostream"
#include "Converter.h"


int main()
{
  std::string buffer;// = "a+b+c";

  std::getline(std::cin, buffer);

  try
  {
    std::cout << "___" << Converter::ConvertToPostfixForm(buffer) << "___" << std::endl;
  }
  catch (MyException const& e)
  {
    std::cout << std::endl << e.what() << std::endl;
    std::cout << "errorLine: " << e.errorLine() << std::endl;
    std::cout << "errorFile: " << e.errorFile() << std::endl;
  }

  Variables var(Converter::getCountOfOperands(), Converter::getOperands());
  var.setValues();

  try
  {
    std::cout << Converter::Calculate(Converter::ConvertToPostfixForm(buffer), var);
  }
  catch (MyException const& e)
  {
    std::cout << std::endl << e.what() << std::endl;
    std::cout << "errorLine: " << e.errorLine() << std::endl;
    std::cout << "errorFile: " << e.errorFile() << std::endl;
  }
  
  Converter::Clear();

  system("pause");
  return 0;
}