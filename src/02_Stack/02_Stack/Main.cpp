#include "iostream"
#include "Converter.h"


int main()
{
  std::string buffer = "a+b+c";
  //std::getline(std::cin, buffer);

  try
  {
    //std::cout << Converter::ConvertToPostfixForm(buffer);
  }
  catch (MyException const& e)
  {
    std::cout << std::endl << e.what() << std::endl;
    std::cout << "errorLine: " << e.errorLine() << std::endl;
    std::cout << "errorFile: " << e.errorFile() << std::endl;
  }

  double d[3] = {1, 2, 3};

  try
  {
    std::cout << Converter::Calculate(Converter::ConvertToPostfixForm(buffer), d);
  }
  catch (MyException const& e)
  {
    std::cout << std::endl << e.what() << std::endl;
    std::cout << "errorLine: " << e.errorLine() << std::endl;
    std::cout << "errorFile: " << e.errorFile() << std::endl;
  }


  system("pause");
  return 0;
}