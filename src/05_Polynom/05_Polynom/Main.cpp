#include "_tListMain.h"
#include "_tPolynomMain.h"

int main()
{
  std::cout << "//~~~~~~~~~~~~~~~~~ Test of class \"TList\" ~~~~~~~~~~~~//" << std::endl << std::endl;
  _tListMain();

  std::cout << "//~~~~~~~~~~~~~~~~ Test of class \"Polynom\" ~~~~~~~~~~~~//" << std::endl << std::endl;
  bool isItAll = false;
  do
  {
    _tPolynomMain();

    std::cout << "Do you want to exit? " << std::endl;
    std::cout << "  1 - Yes     0 - No" << std::endl << std::endl;
    std::cin >> isItAll;
    std::cin.ignore();
  } while (!isItAll);
  system("pause");
  return 0;
}