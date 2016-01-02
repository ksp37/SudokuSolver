#ifndef SUDOKU_SOLVER
#define SUDOKU_SOLVER

#include <vector>


//General Matrix class that acts as a wrapper for a two dimensional STL vector 
class Matrix
{
public:
  Matrix(size_t theRowSize, size_t theColSize);
  virtual int GetValue(size_t theRow, size_t theCol) const;
  virtual bool SetValue(size_t theRow, size_t theCol, int theValue);
  size_t GetColSize(size_t theCol) const;
  size_t GetRowSize(size_t theRow) const;

protected:
  Matrix();

protected:
  std::vector< std::vector<size_t> > m_vectorMatrix;
};

//SudokuMatrix class is used to represent a sudoku grid. Additional methods
//have been provided to ensure the grid stays in a valid state according to 
//sudoku rules. 
class SudokuMatrix : public Matrix
{
  enum{
    //Value for a cell if it is empty.
    EMPTY_VALUE = 0
  };

  public:
    SudokuMatrix();

    //SetValue returns true if theValue has been stored successfully, false otherwise.
    //Note that the method checks that theRow and theCol are within bounds and theValue
    //is legal.
    bool SetValue(size_t theRow, size_t theCol, int theValue);
    int GetValue(size_t theRow, size_t theCol) const;
    
    bool IsValueWithinRange(int theValue) const;

    //Set of methods to check if theValue is already present in a collection of cells.
    //Returns false if so, true otherwise. Note that IsValueLegal() combines checks for
    //the block, row and column.
    bool IsValueLegal(size_t theRow, size_t theCol, int theValue) const;
    bool IsBlockLegal(size_t theRow, size_t theCol, int theValue) const;
    bool IsRowLegal(size_t theRow, int theValue) const;
    bool IsColLegal(size_t theCol, int theValue) const;

};


#endif //SUDOKU_SOLVER