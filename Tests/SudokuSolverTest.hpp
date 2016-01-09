#ifndef SUDOKU_SOLVER_TEST
#define SUDOKU_SOLVER_TEST

#include "..\include\SudokuSolver.hpp"
#include <vector>
#include <set>


//Test class for Matrix
class MatrixTest
{
public:
  virtual bool RunAllTests();

  virtual bool TestGetSetValue() const;
  bool TestGetColSize() const;
  bool TestGetRowSize() const;

};

//Test class for SudokuMatrix
class SudokuMatrixTest : public MatrixTest
{
public:
  virtual bool RunAllTests();

  virtual bool TestGetSetValue() const;
  virtual bool TestClearValue() const;

  bool TestIsValueWithinRange() const;
  bool TestIsBlockLegal() const;
  bool TestIsRowLegal() const;
  bool TestIsColLegal() const;
  bool TestIsSolved() const;
  bool TestGetPossibleValues() const;

};

//Test class for SudokuSolver
class SudokuSolverTest
{
public:
  bool TestSolve();
};

#endif //SUDOKU_SOLVER_TEST