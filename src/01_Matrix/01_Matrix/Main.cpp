#include "TMatrix.h"

int main()
{
  int size;

  std::cout << "Enter size of matrices: ";
  std::cin >> size;
  while (size <= 0)
  {
    std::cout << "Please enter positive integer!" << std::endl;
    std::cin >> size;
  }

  TVector<double> tv(size);
  double tmp;

  TVector<TVector<double> > ttv(size);
  {
    for (int i = 0; i < size; i++)
    {
      TVector<double> temp(size - i, i);
      for (int j = i; j < size; j++)
        temp[j] = 1.;
      ttv[i] = temp;
    } 
  }
  
  TMatrix<double> tm1(size), tm2(size);
  TMatrix<double> tm3, tm4;
  TMatrix<double> tm5(ttv);

  std::cout << "Enter first matrix: " << std::endl;
  std::cin >> tm1;

  TMatrix<double> tm6(tm1);

  std::cout << "Enter second matrix: " << std::endl;
  std::cin >> tm2;
  std::cout << "Enter third matrix (size = 5): " << std::endl;
  std::cin >> tm3;  
  std::cout << "Enter fourth matrix (size = 5): " << std::endl;
  std::cin >> tm4;
  std::cout << "Enter some constant value:" << std::endl;
  std::cin >> tmp;
  std::cout << "Enter vector: " << std::endl;
  std::cin >> tv;
  
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  std::cout << std::endl;

  std::cout << "matrix1: " << std::endl;
  std::cout << tm1 << std::endl;
  std::cout << "matrix2: " << std::endl;
  std::cout << tm2 << std::endl;
  std::cout << "matrix3: " << std::endl;
  std::cout << tm3 << std::endl;
  std::cout << "matrix4: " << std::endl;
  std::cout << tm4 << std::endl;
  std::cout << "matrix5: " << std::endl;
  std::cout << tm5 << std::endl;
  std::cout << "matrix6: " << std::endl;
  std::cout << tm6 << std::endl;

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  std::cout << std::endl;

  std::cout << "(matrix1 == matrix2): " 
      << (tm1 == tm2 ? "true" : "false") << std::endl;
  std::cout << "(matrix1 != matrix2): " 
      << (tm1 != tm2 ? "true" : "false") << std::endl;
  std::cout << "(matrix1 == matrix3): " 
      << (tm1 == tm3 ? "true" : "false") << std::endl;

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  std::cout << std::endl;

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
  std::cout << "matrix3 (matrix3 = matrix1):" << std::endl;
  std::cout << (tm3 = tm1) << std::endl;
  std::cout << "Determinant(matrix1): " << std::endl;
  std::cout << tm1.determinant() << std::endl;

  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  std::cout << std::endl;

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
    tm1[tm1.getSize() + 12];
  }
  catch (VectorExceptionOutOfRange const& e)
  {
    std::cout << std::endl << e.what() << std::endl;
    std::cout << "errorLine: " << e.errorLine() << std::endl;
    std::cout << "errorFile: " << e.errorFile() << std::endl;
  }

  try
  {
    TMatrix<double> tm7(0);
  }
  catch (MyException const& e)
  {
    std::cout << std::endl << e.what() << std::endl;
    std::cout << "errorLine: " << e.errorLine() << std::endl;
    std::cout << "errorFile: " << e.errorFile() << std::endl;
  }

  try
  {
    TVector<TVector<double> > ttv2(0);
  }
  catch (VectorExceptionNotPositiveDimension const& e)
  {
    std::cout << std::endl << e.what() << std::endl;
    std::cout << "errorLine: " << e.errorLine() << std::endl;
    std::cout << "errorFile: " << e.errorFile() << std::endl;
  }

  system("pause");
}