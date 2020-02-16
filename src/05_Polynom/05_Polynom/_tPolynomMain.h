#pragma once
#include "Polynom.h"
#include "stdlib.h"
#include "string"

void _tPolynomMain()
{
  std::cout << std::endl << "//-----------------------------//" << std::endl << std::endl;

  TList<unsigned, double> list1;
  list1.InsertEnd(100, 2);
  list1.InsertEnd(128, -8);
  list1.InsertEnd(101, 11);
  std::cout << list1 << std::endl;
  Polynom tmp1(list1);
  std::cout << tmp1 << std::endl << std::endl;

  TList<unsigned, double> list2;
  list2.InsertEnd(103, 22);
  list2.InsertEnd(306, 78);
  std::cout << list2 << std::endl;
  Polynom tmp2(list2);
  std::cout << tmp2 << std::endl << std::endl;

  std::cout << "Polynom_0: ";
  Polynom polynom_0("2+2x^2+y+z+7y^3");
  std::cout << polynom_0 << std::endl << std::endl;

  try
  {
    std::cout << "  Polynom (or monom) can include " << std::endl;
    std::cout << "    * any real numbers (example: '2', '71.98')," << std::endl;
    std::cout << "    * operands 'x', 'y', 'z'," << std::endl;
    std::cout << "    * mathematical symbols: "-", '+'(only for polynom), '^', '*'" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Please, enter a monom." << std::endl;
    Monom monom;
    std::cin >> monom;
    std::cout << "Monom: " << monom << std::endl << std::endl;

    std::cout << "Please, enter a polynom_1." << std::endl;
    Polynom polynom_1;
    std::cin >> polynom_1;
    std::cout << "Polynom_1: " << polynom_1 << std::endl << std::endl;

    std::cout << "Please, enter a polynom_2." << std::endl;
    Polynom polynom_2;
    std::cin >> polynom_2;
    std::cout << "Polynom_2: " << polynom_2 << std::endl << std::endl;

    std::cout << "Polynom_1 + Monom: " << std::endl;
    std::cout << (polynom_1 + monom) << std::endl << std::endl;

    std::cout << "Polynom_1 - Monom: " << std::endl;
    std::cout << (polynom_1 - monom) << std::endl << std::endl;

    std::cout << "Polynom_1 * Monom: " << std::endl;
    std::cout << (polynom_1 * monom) << std::endl << std::endl;

    std::cout << "Polynom_1 + Polynom_2: " << std::endl;
    std::cout << (polynom_1 + polynom_2) << std::endl << std::endl;

    std::cout << "Polynom_1 - Polynom_2: " << std::endl;
    std::cout << (polynom_1 - polynom_2) << std::endl << std::endl;

    std::cout << "Polynom_1 * Polynom_2: " << std::endl;
    std::cout << (polynom_1 * polynom_2) << std::endl << std::endl;

    std::cout << "Polynom_3 (Polynom_1): " << std::endl;
    Polynom polynom_3(polynom_1);
    std::cout << polynom_3 << std::endl << std::endl;

    std::cout << "Polynom_4 (Monom): " << std::endl;
    Polynom polynom_4(monom);
    std::cout << polynom_4 << std::endl << std::endl;

  }
  catch (MyException const& e)
  {
    std::cout << "  " << e.what() << std::endl;
    std::cout << "  errorLine: " << e.errorLine() << std::endl;
    std::cout << "  errorFile: " << e.errorFile() << std::endl << std::endl;
  }
}