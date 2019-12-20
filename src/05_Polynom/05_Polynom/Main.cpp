#include "Polynom.h"
#include "stdlib.h"
#include "string"

//----------------------------------- TList ---------------------------------//

void _tListMain()
{
  TList<int, std::string> list;
  std::string words[7] = { "I", "She", "He", "It", "We", "You", "They" };

  std::cout << "Insert \"" << words[1] << "\" begin: " << std::endl;
  list.InsertBegin(1, words[1]);
  std::cout << list << std::endl << std::endl;

  std::cout << "Insert \"" << words[3] << "\" after:" << std::endl;
  list.InsertAfter(1, 3, words[3]);
  std::cout << list << std::endl << std::endl;

  std::cout << "Insert \"" << words[2] << "\" before:" << std::endl;
  list.InsertBefore(3, 2, words[2]);
  std::cout << list << std::endl << std::endl;

  std::cout << "Insert \"" << words[4] << "\" end:" << std::endl;
  list.InsertEnd(4, words[4]);
  std::cout << list << std::endl << std::endl;

  std::cout << "Insert \"" << words[5] << "\" after last:" << std::endl;
  list.InsertEnd(5, words[5]);
  std::cout << list << std::endl << std::endl;

  std::cout << "Insert \"" << words[6] << "\" before first:" << std::endl;
  list.InsertBegin(0, words[6]);
  std::cout << list << std::endl << std::endl;

  std::cout << "Remove element with key 0:" << std::endl;
  list.Remove(0);
  std::cout << list << std::endl << std::endl;

  std::cout << "Insert \"" << words[0] << "\" begin:" << std::endl;
  list.InsertBegin(0, words[0]);
  std::cout << list << std::endl << std::endl;

  std::cout << "Constructor copy:" << std::endl;
  std::cout << TList<int, std::string>(list) << std::endl << std::endl;

  std::cout << "Constructor with only node with key \"12\" and data \"" << words[6] << "\"" << std::endl;
  std::cout << TList<int, std::string>(&TNode<int, std::string>(12, words[6])) << std::endl << std::endl;


  std::cout << std::endl << "//-------------//" << std::endl << std::endl;

  TList<unsigned, double> _list1;
  _list1.InsertEnd(100, 2);
  _list1.InsertEnd(101, 11);
  _list1.InsertEnd(128, -8);
  Polynom tmp1(_list1);
  std::cout << tmp1 << std::endl << std::endl;

  TList<unsigned, double> _list2;
  _list2.InsertEnd(103, 22);
  _list2.InsertEnd(306, 78);
  Polynom tmp2(_list2);
  std::cout << tmp2 << std::endl << std::endl;
  
  Polynom tmp3;
  std::cin >> tmp3;
  std::cout << tmp3;
  //std::cout << (tmp1 + tmp2) << std::endl << std::endl;

  std::cout << std::endl << std::endl << "//-------------//" << std::endl;

  try
  {
    std::cout << "Insert \"" << words[0] << "\" after node with key 666:";
    list.InsertAfter(666, 0, words[0]);
    std::cout << list << std::endl;
  }
  catch (MyException const& e)
  {
    std::cout << std::endl << "  " << e.what() << std::endl;
    std::cout << "  errorLine: " << e.errorLine() << std::endl;
    std::cout << "  errorFile: " << e.errorFile() << std::endl << std::endl;
  }

  try
  {
    std::cout << "Insert \"" << words[0] << "\" before node with key 666:" << std::endl;
    list.InsertBefore(666, 0, words[0]);
    std::cout << list << std::endl;
  }
  catch (MyException const& e)
  {
    std::cout << "  " << e.what() << std::endl;
    std::cout << "  errorLine: " << e.errorLine() << std::endl;
    std::cout << "  errorFile: " << e.errorFile() << std::endl << std::endl;
  }

  try
  {
    std::cout << "Remove element with key 666:" << std::endl;
    list.Remove(666);
    std::cout << list << std::endl;
  }
  catch (MyException const& e)
  {
    std::cout << "  " << e.what() << std::endl;
    std::cout << "  errorLine: " << e.errorLine() << std::endl;
    std::cout << "  errorFile: " << e.errorFile() << std::endl << std::endl;
  }
}


//---------------------------------- Polynom -------------------------------//

void _tListMain()
{
  try
  {
  std::cout << std::endl << "//-----------------------------//" << std::endl << std::endl;

  TList<unsigned, double> _list1;
  _list1.InsertEnd(100, 2);
  _list1.InsertEnd(101, 11);
  _list1.InsertEnd(128, -8);
  Polynom tmp1(_list1);
  std::cout << tmp1 << std::endl << std::endl;

  TList<unsigned, double> _list2;
  _list2.InsertEnd(103, 22);
  _list2.InsertEnd(306, 78);
  Polynom tmp2(_list2);
  std::cout << tmp2 << std::endl << std::endl;

  Polynom tmp3;
  std::cin >> tmp3;
  std::cout << tmp3;

  std::cout << std::endl << (tmp1 + tmp2) << std::endl << std::endl;

  Polynom tmp4;
  std::cin >> tmp4;
  std::cout << tmp4;


  std::cout << std::endl << (tmp3 + tmp4) << std::endl << std::endl;

  std::cout << std::endl << std::endl << "//-------------//" << std::endl;

  }
  catch (MyException const& e)
  {
    std::cout << "  " << e.what() << std::endl;
    std::cout << "  errorLine: " << e.errorLine() << std::endl;
    std::cout << "  errorFile: " << e.errorFile() << std::endl << std::endl;
  }
}

//------------------------------------ Main ---------------------------------//

int main()
{
  std::cout << "//~~~~~~~~~~~~~~~~~ Test of class \"TList\" ~~~~~~~~~~~~//" << std::endl << std::endl;
  _tListMain();

  std::cout << "//~~~~~~~~~~~~~~~~ Test of class \"Polynom\" ~~~~~~~~~~~~//" << std::endl << std::endl;
  bool isItAll = false;
  do
  {

    std::cout << "Do you want to exit?" << std::endl;
    std::cout << "  1 - Yes     0 - No" << std::endl << std::endl;
    std::cin >> isItAll;
    std::cin.ignore();
  } while (!isItAll);
  system("pause");
  return 0;
}