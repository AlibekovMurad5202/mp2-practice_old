#include "TMatrix.h"

int main()
{
  unsigned size;

  std::cout << std::endl << "Enter size of matrices: ";
  std::cin >> size;

  TMatrix<double> tm1(size), tm2(size), tm3, tm4;
  TVector<double> tv(size);
  double tmp;

  std::cout << "Enter first matrix: " << std::endl;
  std::cin >> tm1;
  std::cout << "Enter second matrix: " << std::endl;
  std::cin >> tm2;
  std::cout << "Enter third matrix (size = 7): " << std::endl;
  std::cin >> tm2;  
  std::cout << "Enter fourth matrix (size = 7): " << std::endl;
  std::cin >> tm2;
  std::cout << "Enter some constant value:" << std::endl;
  std::cin >> tmp;
  std::cout << "Enter vector: " << std::endl;
  std::cin >> tv;

  std::cout << "(matrix1 == matrix2): " << (tm1 == tm2) << std::endl;
  std::cout << "(matrix1 != matrix2): " << (tm1 != tm2) << std::endl;
  std::cout << "(matrix1 == matrix3): " << (tm1 == tm3) << std::endl;

  std::cout << "matrix1 + value:" << std::endl;
  std::cout << (tm1 + tmp) << std::endl;
  std::cout << "matrix1 - value:" << std::endl;
  std::cout << (tm1 - tmp) << std::endl;
  std::cout << "matrix1 * value:" << std::endl;
  std::cout << (tm1 * tmp) << std::endl;

  std::cout << "matrix1 + matrix2:" << std::endl;
  std::cout << tm1 + tm2 << std::endl;
  std::cout << "matrix1 - matrix2:" << std::endl;
  std::cout << tm1 - tm2 << std::endl;
  std::cout << "matrix1 * matrix2:" << std::endl;
  std::cout << tm1 * tm2 << std::endl;

  std::cout << "matrix1 * vector:" << std::endl;
  std::cout << tm1 * tmp << std::endl;

  std::cout << "matrix3 = matrix1:" << std::endl;
  std::cout << (tm3 = tm1) << std::endl;

  std::cout << "Determinant(matrix1): " << std::endl;
  std::cout << tm1.determinant() << std::endl;

  try
  {
    tm1 * tm4;
  }
  catch (MatrixExceptionDifferentDimensions const& e)
  {
    std::cout << std::endl << e.what() << std::endl;
    std::cout << "errorLine: " << e.errorLine() << std::endl;
    std::cout << "errorFile: " << e.errorFile() << std::endl;
  }

  try
  {
    tm1[73];
  }
  catch (VectorExceptionOutOfRange const& e)
  {
    std::cout << std::endl << e.what() << std::endl;
    std::cout << "errorLine: " << e.errorLine() << std::endl;
    std::cout << "errorFile: " << e.errorFile() << std::endl;
  }

  system("pause");
}