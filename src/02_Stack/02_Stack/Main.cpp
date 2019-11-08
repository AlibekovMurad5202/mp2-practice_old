#include "Converter.h"

int main()
{
  std::cout << "Expression can include " << std::endl;
  std::cout << "  * real numbers (example: '2', '71.98')," << std::endl;
  std::cout << "  * operands (example: 'x', 'B', 'asdf', 'amr12')," << std::endl;
  std::cout << "  * mathematical symbols: '+', '-', '*', '/', '(', ')'" << std::endl;

  bool isItAll = false;

  do
  {
    std::cout << std::endl << "Please, enter an expression.";
    std::cout << std::endl << "Expression: ";
    std::string buffer;
    std::getline(std::cin, buffer);

    try
    {
      std::cout << "Postfix form: " << Converter::ConvertToPostfixForm(buffer) << std::endl;

      Variables var(Converter::operands);
      
      std::cout << "Result: ";
      std::cout << Converter::Calculate(Converter::ConvertToPostfixForm(buffer), var);
      std::cout << std::endl << std::endl;
      Converter::Clear();
    }
    catch (MyException const& e)
    {
      std::cout << std::endl << e.what() << std::endl;
      std::cout << "errorLine: " << e.errorLine() << std::endl;
      std::cout << "errorFile: " << e.errorFile() << std::endl;
    }

    std::cout << "Do you want to exit?" << std::endl;
    std::cout << "1 - Yes       0 - No" << std::endl;
    std::cin >> isItAll;
    std::cin.ignore();
  } while (!isItAll);

  system("pause");
  return 0;
}