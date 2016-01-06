#ifndef SUDOKU_SOLVER
#define SUDOKU_SOLVER

#include <vector>
#include <set>


//General Matrix class that acts as a wrapper for a two dimensional STL vector 
class Matrix
{
public:

  enum{
    //Value for a cell if it is empty.
    EMPTY_VALUE = 0,
    //Value returned by GetValue() if parameters are out of bounds
    OUT_OF_BOUNDS = -1
  };

  Matrix(size_t theRowSize, size_t theColSize);
  virtual int GetValue(size_t theRow, size_t theCol) const;
  virtual bool SetValue(size_t theRow, size_t theCol, int theValue);
  size_t GetColSize() const;
  size_t GetRowSize() const;

protected:
  std::vector< std::vector<size_t> > m_vectorMatrix;
  size_t m_noCols, m_noRows;
};

//SudokuMatrix class is used to represent a sudoku grid. Additional methods
//have been provided to ensure the grid stays in a valid state according to 
//sudoku rules. 
class SudokuMatrix : public Matrix
{
  public:
    SudokuMatrix();

    //SetValue() returns true if theValue has been stored successfully, false otherwise.
    //Note that the method checks that theRow and theCol are within bounds and theValue
    //is legal.
    virtual bool SetValue(size_t theRow, size_t theCol, int theValue);
    virtual int GetValue(size_t theRow, size_t theCol) const;
    virtual bool ClearValue(size_t theRow, size_t theCol);
    
    bool IsValueWithinRange(int theValue) const;

    //Set of methods to check if theValue is already present in a collection of cells.
    //Returns false if so, true otherwise. Note that IsValueLegal() combines checks for
    //the block, row and column.
    bool IsValueLegal(size_t theRow, size_t theCol, int theValue) const;
    bool IsBlockLegal(size_t theRow, size_t theCol, int theValue) const;
    bool IsRowLegal(size_t theRow, int theValue) const;
    bool IsColLegal(size_t theCol, int theValue) const;

    //IsSolved() returns true if no empty entries are found. By virtue of SetValue(), if the
    //matrix is fully populated it must also be solved.
    bool IsSolved() const;

    //Returns the set of legal values for theRow and theCol.
    std::set<int> GetPossibleValues(size_t theRow, size_t theCol) const;

  protected:
    std::set<int> m_possibleValuesSet;

};

class SudokuSolver
{
  public:
    //An instance must be initialised with anInitialMatrix. The shouldPreprocess flag
    //indicates if the solver should scan the matrix first to determine an ideal order to
    //visit cells (default ordering is from left to right then top to bottom).
    SudokuSolver(const SudokuMatrix & theInitialMatrix, bool shouldPreprocess = false);
    const SudokuMatrix & Solve();
    const SudokuMatrix & GetSolutionMatrix();

  protected:
    SudokuMatrix m_matrix;
    bool m_preprocessFlag;
    std::vector< std::pair<size_t,size_t> > m_permutatedIndices;

  private:
    void DoPreprocessing();
    bool PopulateMatrix(size_t theIndex);

};

#endif //SUDOKU_SOLVER