#include "SudokuSolverTest.hpp"
#include <iostream>

bool MatrixTest::RunAllTests()
{
  int noPassed = 0;
  int noFailed = 0;

  std::cout << "++++++++ RUNNING TESTS FOR MATRIX CLASS ++++++++" << std::endl; 

  if (TestGetSetValue())
  {
    std::cout << "TestGetSetValue      : Passed" << std::endl;
    noPassed++;
  }
  else
  {
    std::cout << "TestGetSetValue      : Failed" << std::endl;
    noFailed++;
  }

  if (TestGetColSize())
  {
    std::cout << "TestGetColSize       : Passed" << std::endl;
    noPassed++;
  }
  else
  {
    std::cout << "TestGetColSize       : Failed" << std::endl;
    noFailed++;
  }

  if (TestGetRowSize())
  {
    std::cout << "TestGetRowSize       : Passed" << std::endl;
    noPassed++;
  }
  else
  {
    std::cout << "TestGetRowSize       : Failed" << std::endl;
    noFailed++;
  }

  std::cout << "SUMMARY: " << noPassed << " tests passed. " << noFailed << " tests failed." << std::endl;

  return noFailed == 0;
}

bool MatrixTest::TestGetSetValue() const
{
  Matrix testMatrix(5, 10);

  bool boundsCheck =
    !testMatrix.SetValue(4, 10, 1) && !testMatrix.SetValue(5, 9, 1)
    && testMatrix.GetValue(4, 10) == Matrix::OUT_OF_BOUNDS
    && testMatrix.GetValue(5, 9) == Matrix::OUT_OF_BOUNDS;

  testMatrix.SetValue(3, 3, 3);
  bool functionCheck = (testMatrix.GetValue(3, 3) == 3);

  return boundsCheck && functionCheck;
}


bool MatrixTest::TestGetColSize() const
{
  Matrix testMatrix(5, 10);
  
  return testMatrix.GetColSize() == 10;
}

bool MatrixTest::TestGetRowSize() const
{
  Matrix testMatrix(5, 10);

  return testMatrix.GetRowSize() == 5;
}

//-----------------------------------------------------------------------------------------------//

bool SudokuMatrixTest::RunAllTests()
{
  int noPassed = 0;
  int noFailed = 0;

  std::cout << "++++++++ RUNNING TESTS FOR SUDOKUMATRIX CLASS ++++++++" << std::endl;

  if (TestGetSetValue())
  {
    std::cout << "TestGetSetValue              : Passed" << std::endl;
    noPassed++;
  }
  else
  {
    std::cout << "TestGetSetValue              : Failed" << std::endl;
    noFailed++;
  }

  if (TestClearValue())
  {
    std::cout << "TestClearValue               : Passed" << std::endl;
    noPassed++;
  }
  else
  {
    std::cout << "TestClearValue               : Failed" << std::endl;
    noFailed++;
  }

  if (TestIsValueWithinRange())
  {
    std::cout << "TestIsValueWithinRange       : Passed" << std::endl;
    noPassed++;
  }
  else
  {
    std::cout << "TestIsValueWithinRange       : Failed" << std::endl;
    noFailed++;
  }

  if (TestIsBlockLegal())
  {
    std::cout << "TestIsBlockLegal             : Passed" << std::endl;
    noPassed++;
  }
  else
  {
    std::cout << "TestIsBlockLegal             : Failed" << std::endl;
    noFailed++;
  }

  if (TestIsRowLegal())
  {
    std::cout << "TestIsRowLegal               : Passed" << std::endl;
    noPassed++;
  }
  else
  {
    std::cout << "TestIsRowLegal               : Failed" << std::endl;
    noFailed++;
  }

  if (TestIsColLegal())
  {
    std::cout << "TestIsColLegal               : Passed" << std::endl;
    noPassed++;
  }
  else
  {
    std::cout << "TestIsColLegal               : Failed" << std::endl;
    noFailed++;
  }

  if (TestIsSolved())
  {
    std::cout << "TestIsSolved                 : Passed" << std::endl;
    noPassed++;
  }
  else
  {
    std::cout << "TestIsSolved                 : Failed" << std::endl;
    noFailed++;
  }

  if (TestGetPossibleValues())
  {
    std::cout << "TestGetPossibleValues        : Passed" << std::endl;
    noPassed++;
  }
  else
  {
    std::cout << "TestGetPossibleValues        : Failed" << std::endl;
    noFailed++;
  }

  std::cout << "SUMMARY: " << noPassed << " tests passed. " << noFailed << " tests failed." << std::endl;

  return noFailed == 0;
}

bool SudokuMatrixTest::TestGetSetValue() const
{
  SudokuMatrix testMatrix;

  bool boundsCheck =
    !testMatrix.SetValue(8, 9, 1) && !testMatrix.SetValue(9, 8, 1)
    && testMatrix.GetValue(8, 9) == Matrix::OUT_OF_BOUNDS
    && testMatrix.GetValue(9, 8) == Matrix::OUT_OF_BOUNDS;

  testMatrix.SetValue(1, 1, 3);

  bool functionCheck =
    !testMatrix.SetValue(5, 1, 3) //test duplicate in row
    && !testMatrix.SetValue(1, 5, 3)  //test duplicate in col
    && !testMatrix.SetValue(0, 0, 3)  //test duplicate in block
    && !testMatrix.SetValue(6, 8, 10) //test value range 
    && testMatrix.SetValue(0, 0, 2)
    && testMatrix.GetValue(0, 0) == 2;

  return boundsCheck && functionCheck;
}


bool SudokuMatrixTest::TestClearValue() const
{
  SudokuMatrix testMatrix;

  bool boundsCheck =
    !testMatrix.ClearValue(8, 9) && !testMatrix.ClearValue(9, 8);

  testMatrix.SetValue(1, 1, 3);
  testMatrix.ClearValue(1, 1);

  return boundsCheck && testMatrix.GetValue(1, 1) == Matrix::EMPTY_VALUE;
}

bool SudokuMatrixTest::TestIsValueWithinRange() const
{
  SudokuMatrix testMatrix;
  bool rangeCheck =
    !testMatrix.IsValueWithinRange(0)
    && !testMatrix.IsValueWithinRange(10)
    && testMatrix.IsValueWithinRange(9);

    return rangeCheck;
}

bool SudokuMatrixTest::TestIsBlockLegal() const
{
  SudokuMatrix testMatrix;

  bool boundsCheck =
    !testMatrix.IsBlockLegal(8, 9, 1) && !testMatrix.IsBlockLegal(9, 8, 1);

  testMatrix.SetValue(8, 8, 5);

  bool legalCheck =
    !testMatrix.IsBlockLegal(7, 7, 5)
    && !testMatrix.IsBlockLegal(7, 7, 10)
    && testMatrix.IsBlockLegal(7, 7, 6);

  return boundsCheck && legalCheck;
}

bool SudokuMatrixTest::TestIsRowLegal() const
{
  SudokuMatrix testMatrix;

  bool boundsCheck = !testMatrix.IsRowLegal(9, 1);

  testMatrix.SetValue(8, 1, 5);

  bool legalCheck =
    !testMatrix.IsRowLegal(8, 5)
    && !testMatrix.IsRowLegal(8, 10)
    && testMatrix.IsRowLegal(8, 2);


  return boundsCheck && legalCheck;
}

bool SudokuMatrixTest::TestIsColLegal() const
{
  SudokuMatrix testMatrix;

  bool boundsCheck = !testMatrix.IsColLegal(9, 1);

  testMatrix.SetValue(8, 1, 5);

  bool legalCheck =
    !testMatrix.IsColLegal(1, 5)
    && !testMatrix.IsColLegal(1, 10)
    && testMatrix.IsColLegal(1, 2);

  return boundsCheck && legalCheck;
}

bool SudokuMatrixTest::TestIsSolved() const
{
  SudokuMatrix testMatrix;
  testMatrix.SetValue(0, 0, 1);
  testMatrix.SetValue(0, 1, 2);
  testMatrix.SetValue(0, 2, 3);
  testMatrix.SetValue(0, 3, 4);
  testMatrix.SetValue(0, 4, 5);
  testMatrix.SetValue(0, 5, 6);
  testMatrix.SetValue(0, 6, 7);
  testMatrix.SetValue(0, 7, 8);
  testMatrix.SetValue(0, 8, 9);

  testMatrix.SetValue(1, 0, 4);
  testMatrix.SetValue(1, 1, 5);
  testMatrix.SetValue(1, 2, 6);
  testMatrix.SetValue(1, 3, 7);
  testMatrix.SetValue(1, 4, 8);
  testMatrix.SetValue(1, 5, 9);
  testMatrix.SetValue(1, 6, 1);
  testMatrix.SetValue(1, 7, 2);
  testMatrix.SetValue(1, 8, 3);

  testMatrix.SetValue(2, 0, 7);
  testMatrix.SetValue(2, 1, 8);
  testMatrix.SetValue(2, 2, 9);
  testMatrix.SetValue(2, 3, 1);
  testMatrix.SetValue(2, 4, 2);
  testMatrix.SetValue(2, 5, 3);
  testMatrix.SetValue(2, 6, 4);
  testMatrix.SetValue(2, 7, 5);
  testMatrix.SetValue(2, 8, 6);

  testMatrix.SetValue(3, 0, 2);
  testMatrix.SetValue(3, 1, 1);
  testMatrix.SetValue(3, 2, 4);
  testMatrix.SetValue(3, 3, 3);
  testMatrix.SetValue(3, 4, 6);
  testMatrix.SetValue(3, 5, 5);
  testMatrix.SetValue(3, 6, 8);
  testMatrix.SetValue(3, 7, 9);
  testMatrix.SetValue(3, 8, 7);

  testMatrix.SetValue(4, 0, 3);
  testMatrix.SetValue(4, 1, 6);
  testMatrix.SetValue(4, 2, 7);
  testMatrix.SetValue(4, 3, 8);
  testMatrix.SetValue(4, 4, 9);
  testMatrix.SetValue(4, 5, 1);
  testMatrix.SetValue(4, 6, 2);
  testMatrix.SetValue(4, 7, 4);
  testMatrix.SetValue(4, 8, 5);

  testMatrix.SetValue(5, 0, 5);
  testMatrix.SetValue(5, 1, 9);
  testMatrix.SetValue(5, 2, 8);
  testMatrix.SetValue(5, 3, 2);
  testMatrix.SetValue(5, 4, 4);
  testMatrix.SetValue(5, 5, 7);
  testMatrix.SetValue(5, 6, 3);
  testMatrix.SetValue(5, 7, 6);
  testMatrix.SetValue(5, 8, 1);

  testMatrix.SetValue(6, 0, 6);
  testMatrix.SetValue(6, 1, 3);
  testMatrix.SetValue(6, 2, 2);
  testMatrix.SetValue(6, 3, 5);
  testMatrix.SetValue(6, 4, 1);
  testMatrix.SetValue(6, 5, 4);
  testMatrix.SetValue(6, 6, 9);
  testMatrix.SetValue(6, 7, 7);
  testMatrix.SetValue(6, 8, 8);

  testMatrix.SetValue(7, 0, 8);
  testMatrix.SetValue(7, 1, 7);
  testMatrix.SetValue(7, 2, 5);
  testMatrix.SetValue(7, 3, 9);
  testMatrix.SetValue(7, 4, 3);
  testMatrix.SetValue(7, 5, 2);
  testMatrix.SetValue(7, 6, 6);
  testMatrix.SetValue(7, 7, 1);
  testMatrix.SetValue(7, 8, 4);

  testMatrix.SetValue(8, 0, 9);
  testMatrix.SetValue(8, 1, 4);
  testMatrix.SetValue(8, 2, 1);
  testMatrix.SetValue(8, 3, 6);
  testMatrix.SetValue(8, 4, 7);
  testMatrix.SetValue(8, 5, 8);
  testMatrix.SetValue(8, 6, 5);
  testMatrix.SetValue(8, 7, 3);
  testMatrix.SetValue(8, 8, 2);

  bool solvedCheck = testMatrix.IsSolved();

  testMatrix.ClearValue(0, 8);

  if (testMatrix.IsSolved())
  {
    solvedCheck = false;
  }
 
  return solvedCheck;
}

bool SudokuMatrixTest::TestGetPossibleValues() const
{
  SudokuMatrix testMatrix;
  testMatrix.SetValue(6, 4, 1);
  testMatrix.SetValue(4, 6, 2);
  testMatrix.SetValue(5, 5, 3);
  testMatrix.SetValue(8, 8, 4);

  std::set<int> remainingValues = testMatrix.GetPossibleValues(4,4);

  for (size_t val = 4; val < 10; val++)
  {
    if (remainingValues.find(val) == remainingValues.end())
    {
      return false;
    }
  }

  return true;
}

//-----------------------------------------------------------------------------------------------//

bool SudokuSolverTest::TestSolve()
{
  SudokuMatrix testMatrix, solutionMatrix;

  solutionMatrix.SetValue(0, 0, 1);
  solutionMatrix.SetValue(0, 1, 2);
  solutionMatrix.SetValue(0, 2, 3);
  solutionMatrix.SetValue(0, 3, 4);
  solutionMatrix.SetValue(0, 4, 5);
  solutionMatrix.SetValue(0, 5, 6);
  solutionMatrix.SetValue(0, 6, 7);
  solutionMatrix.SetValue(0, 7, 8);
  solutionMatrix.SetValue(0, 8, 9);

  solutionMatrix.SetValue(1, 0, 4);
  solutionMatrix.SetValue(1, 1, 5);
  solutionMatrix.SetValue(1, 2, 6);
  solutionMatrix.SetValue(1, 3, 7);
  solutionMatrix.SetValue(1, 4, 8);
  solutionMatrix.SetValue(1, 5, 9);
  solutionMatrix.SetValue(1, 6, 1);
  solutionMatrix.SetValue(1, 7, 2);
  solutionMatrix.SetValue(1, 8, 3);

  solutionMatrix.SetValue(2, 0, 7);
  solutionMatrix.SetValue(2, 1, 8);
  solutionMatrix.SetValue(2, 2, 9);
  solutionMatrix.SetValue(2, 3, 1);
  solutionMatrix.SetValue(2, 4, 2);
  solutionMatrix.SetValue(2, 5, 3);
  solutionMatrix.SetValue(2, 6, 4);
  solutionMatrix.SetValue(2, 7, 5);
  solutionMatrix.SetValue(2, 8, 6);

  solutionMatrix.SetValue(3, 0, 2);
  solutionMatrix.SetValue(3, 1, 1);
  solutionMatrix.SetValue(3, 2, 4);
  solutionMatrix.SetValue(3, 3, 3);
  solutionMatrix.SetValue(3, 4, 6);
  solutionMatrix.SetValue(3, 5, 5);
  solutionMatrix.SetValue(3, 6, 8);
  solutionMatrix.SetValue(3, 7, 9);
  solutionMatrix.SetValue(3, 8, 7);

  solutionMatrix.SetValue(4, 0, 3);
  solutionMatrix.SetValue(4, 1, 6);
  solutionMatrix.SetValue(4, 2, 7);
  solutionMatrix.SetValue(4, 3, 8);
  solutionMatrix.SetValue(4, 4, 9);
  solutionMatrix.SetValue(4, 5, 1);
  solutionMatrix.SetValue(4, 6, 2);
  solutionMatrix.SetValue(4, 7, 4);
  solutionMatrix.SetValue(4, 8, 5);

  solutionMatrix.SetValue(5, 0, 5);
  solutionMatrix.SetValue(5, 1, 9);
  solutionMatrix.SetValue(5, 2, 8);
  solutionMatrix.SetValue(5, 3, 2);
  solutionMatrix.SetValue(5, 4, 4);
  solutionMatrix.SetValue(5, 5, 7);
  solutionMatrix.SetValue(5, 6, 3);
  solutionMatrix.SetValue(5, 7, 6);
  solutionMatrix.SetValue(5, 8, 1);

  solutionMatrix.SetValue(6, 0, 6);
  solutionMatrix.SetValue(6, 1, 3);
  solutionMatrix.SetValue(6, 2, 2);
  solutionMatrix.SetValue(6, 3, 5);
  solutionMatrix.SetValue(6, 4, 1);
  solutionMatrix.SetValue(6, 5, 4);
  solutionMatrix.SetValue(6, 6, 9);
  solutionMatrix.SetValue(6, 7, 7);
  solutionMatrix.SetValue(6, 8, 8);

  solutionMatrix.SetValue(7, 0, 8);
  solutionMatrix.SetValue(7, 1, 7);
  solutionMatrix.SetValue(7, 2, 5);
  solutionMatrix.SetValue(7, 3, 9);
  solutionMatrix.SetValue(7, 4, 3);
  solutionMatrix.SetValue(7, 5, 2);
  solutionMatrix.SetValue(7, 6, 6);
  solutionMatrix.SetValue(7, 7, 1);
  solutionMatrix.SetValue(7, 8, 4);

  solutionMatrix.SetValue(8, 0, 9);
  solutionMatrix.SetValue(8, 1, 4);
  solutionMatrix.SetValue(8, 2, 1);
  solutionMatrix.SetValue(8, 3, 6);
  solutionMatrix.SetValue(8, 4, 7);
  solutionMatrix.SetValue(8, 5, 8);
  solutionMatrix.SetValue(8, 6, 5);
  solutionMatrix.SetValue(8, 7, 3);
  solutionMatrix.SetValue(8, 8, 2);

  testMatrix.SetValue(0, 0, 1);
  testMatrix.SetValue(0, 3, 4);
  testMatrix.SetValue(0, 5, 6);
  testMatrix.SetValue(0, 6, 7);
  testMatrix.SetValue(0, 8, 9);

  testMatrix.SetValue(1, 0, 4);
  testMatrix.SetValue(1, 2, 6);
  testMatrix.SetValue(1, 3, 7);
  testMatrix.SetValue(1, 5, 9);
  testMatrix.SetValue(1, 6, 1);
  testMatrix.SetValue(1, 7, 2);

  testMatrix.SetValue(2, 3, 1);
  testMatrix.SetValue(2, 4, 2);
  testMatrix.SetValue(2, 5, 3);
  testMatrix.SetValue(2, 6, 4);
  testMatrix.SetValue(2, 7, 5);
  testMatrix.SetValue(2, 8, 6);

  testMatrix.SetValue(3, 0, 2);
  testMatrix.SetValue(3, 1, 1);
  testMatrix.SetValue(3, 2, 4);
  testMatrix.SetValue(3, 3, 3);
  testMatrix.SetValue(3, 4, 6);
  testMatrix.SetValue(3, 5, 5);

  testMatrix.SetValue(4, 0, 3);
  testMatrix.SetValue(4, 1, 6);
  testMatrix.SetValue(4, 3, 8);
  testMatrix.SetValue(4, 5, 1);
  testMatrix.SetValue(4, 7, 4);
  testMatrix.SetValue(4, 8, 5);

  testMatrix.SetValue(5, 2, 8);
  testMatrix.SetValue(5, 3, 2);
  testMatrix.SetValue(5, 4, 4);
  testMatrix.SetValue(5, 5, 7);
  testMatrix.SetValue(5, 6, 3);

  testMatrix.SetValue(6, 1, 3);
  testMatrix.SetValue(6, 2, 2);
  testMatrix.SetValue(6, 4, 1);
  testMatrix.SetValue(6, 6, 9);
  testMatrix.SetValue(6, 7, 7);

  testMatrix.SetValue(7, 0, 8);
  testMatrix.SetValue(7, 1, 7);
  testMatrix.SetValue(7, 2, 5);
  testMatrix.SetValue(7, 5, 2);
  testMatrix.SetValue(7, 6, 6);

  testMatrix.SetValue(8, 0, 9);
  testMatrix.SetValue(8, 3, 6);
  testMatrix.SetValue(8, 4, 7);
  testMatrix.SetValue(8, 5, 8);
  testMatrix.SetValue(8, 7, 3);

  SudokuSolver solver(testMatrix, true);
  SudokuMatrix solvedMatrix = solver.Solve();

  for (size_t i = 0; i < 10; i++)
  {
    for (size_t j = 0; j < 10; j++)
    {
      if (solvedMatrix.GetValue(i, j) != solutionMatrix.GetValue(i, j))
      {
        return false;
      }
    }
  }

  return true;
}
