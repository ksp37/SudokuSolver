#include "SudokuSolverTest.hpp"
#include <iostream>

int main()
{
  MatrixTest testOne;
  testOne.RunAllTests();

  SudokuMatrixTest testTwo;
  testTwo.RunAllTests();

  SudokuSolverTest testThree;
  if (testThree.TestSolve())
  {
    std::cout << "SudokuSolver::Solve()      : Passed" << std::endl;
  }
  else
  {
    std::cout << "SudokuSolver::Solve()      : Failed" << std::endl;
  }
  return 0;
}