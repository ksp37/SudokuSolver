#include "SudokuSolver.hpp"
#include <algorithm>
#include <functional>
#include <iterator>

Matrix::Matrix(size_t theRowSize, size_t theColSize)
{
  m_noCols = theRowSize;
  m_noRows = theColSize;

  for (size_t i = 0; i < theRowSize; i++)
  {
    m_vectorMatrix.push_back(std::vector<size_t>(theColSize, 0));
  }
}

int Matrix::GetValue(size_t theRow, size_t theCol) const
{
  if (theRow < m_noRows && theCol < m_noCols)
  {
    return m_vectorMatrix[theRow][theCol];
  }
  else
  {
    return OUT_OF_BOUNDS;
  }
}

bool Matrix::SetValue(size_t theRow, size_t theCol, int theValue)
{
  if (theRow < m_noRows && theCol < m_noCols)
  {
    m_vectorMatrix[theRow][theCol] = theValue;
    return true;
  }
  else
  {
    return false;
  }
}

size_t Matrix::GetColSize() const 
{
  return m_noRows;
}


size_t Matrix::GetRowSize() const
{
  return m_noCols;
}



//-----------------------------------------------------------------------------------------------//


SudokuMatrix::SudokuMatrix()
  : Matrix(9,9)
{
  for (size_t value = 1; value < 10; value++)
  {
    m_possibleValuesSet.insert(value);
  }
  m_possibleValuesSet.insert(EMPTY_VALUE);
}


int SudokuMatrix::GetValue(size_t theRow, size_t theCol) const
{
  if (theRow < m_noRows && theCol < m_noCols)
  {
    return m_vectorMatrix[theRow][theCol];
  }
  else
  {
    return OUT_OF_BOUNDS;
  }
}

bool SudokuMatrix::SetValue(size_t theRow, size_t theCol, int theValue)
{
  if (theRow < m_noRows 
    && theCol < m_noCols
    && IsValueLegal(theRow, theCol, theValue)
    )
  {
    m_vectorMatrix[theRow][theCol] = theValue;
    return true;
  }
  else
  {
    return false;
  }
}

bool SudokuMatrix::ClearValue(size_t theRow, size_t theCol)
{
  if (theRow < m_noRows
    && theCol < m_noCols
    )
  {
    m_vectorMatrix[theRow][theCol] = EMPTY_VALUE;
    return true;
  }

  return false;
}

bool SudokuMatrix::IsValueWithinRange(int theValue) const
{
  return (theValue < 10 && theValue > 0);
}

bool SudokuMatrix::IsValueLegal(size_t theRow, size_t theCol, int theValue) const
{
  return IsBlockLegal(theRow, theCol, theValue) && IsRowLegal(theRow, theValue) && IsColLegal(theCol, theValue);
}


bool SudokuMatrix::IsBlockLegal(size_t theRow, size_t theCol, int theValue) const
{
  //Get top left cell for block
  int blockRowStart = (int)theRow / 3; 
  int blockColStart = (int)theCol / 3;

  if ((blockRowStart + 1) * 3 > m_noRows
    || (blockColStart + 1) * 3 > m_noCols
    || !IsValueWithinRange(theValue)
    )
  {
    // out of bounds or value range error
    return false;
  }

  for (size_t i = blockRowStart * 3; i < (blockRowStart + 1) * 3; i++)
  {
    for (size_t j = blockColStart * 3; j < (blockColStart + 1) * 3; j++)
    {
      if (m_vectorMatrix[i][j] == theValue)
      {
        return false;
      }
    }
  }

  return true;
}

bool SudokuMatrix::IsRowLegal(size_t theRow, int theValue) const
{
  if (theRow >= m_noRows
    || !IsValueWithinRange(theValue)
    )
  {
    // out of bounds or value range error
    return false;
  }

  for (size_t i = 0; i < m_noCols; i++)
  {
    if (m_vectorMatrix[theRow][i] == theValue)
    {
      return false;
    }
  }

  return true;
}


bool SudokuMatrix::IsColLegal(size_t theCol, int theValue) const
{
  for (size_t i = 0; i < m_noRows; i++)
  {
    if (theCol >= m_noCols
      || !IsValueWithinRange(theValue)
      )
    {
      // out of bounds or value range error
      return false;
    }
  }

  for (size_t i = 0; i < m_noRows; i++)
  {
    if (m_vectorMatrix[i][theCol] == theValue)
    {
      return false;
    }
  }

  return true;
}

std::set<int> SudokuMatrix::GetPossibleValues(size_t theRow, size_t theCol) const
{
  std::set<int> currentSet, remainingSet;
  int blockRowStart = (int)theRow / 3;
  int blockColStart = (int)theCol / 3;
  currentSet.insert(EMPTY_VALUE);

  if (theRow >= m_noRows || theCol >= m_noCols)
  {
    return remainingSet;
  }

  //Insert neighbouring values from block, row and column.
  for (size_t i = blockRowStart * 3; i < (blockRowStart + 1) * 3; i++)
  {
    for (size_t j = blockColStart * 3; j < (blockColStart + 1) * 3; j++)
    {
      currentSet.insert(m_vectorMatrix[i][j]);
    }
  }

  for (size_t i = 0; i < m_noCols; i++)
  {
    currentSet.insert(m_vectorMatrix[theRow][i]);
  }

  for (size_t i = 0; i < m_noRows; i++)
  {
    currentSet.insert(m_vectorMatrix[i][theCol]);
  }

  //Take the set difference with all the possible values to get all legal values
  std::insert_iterator< std::set<int> > insert_it(remainingSet, remainingSet.begin());
  std::set_difference(m_possibleValuesSet.begin(), m_possibleValuesSet.end(),
    currentSet.begin(), currentSet.end(),
    insert_it
    );

  return remainingSet;
}

bool SudokuMatrix::IsSolved() const
{
  //SetValue() ensures that matrix is solved if and only if the matrix
  //is fully populated. Therefore just need to check for any empty cells.

  for (size_t i = 0; i < m_noRows; i++)
  {
    for (size_t j = 0; j < m_noCols; j++)
    {
      if (m_vectorMatrix[i][j] == EMPTY_VALUE)
      {
        return false;
      }
    }
  }
  return true;
}

//-----------------------------------------------------------------------------------------------//

SudokuSolver::SudokuSolver(const SudokuMatrix & theInitialMatrix, bool shouldPreprocess)
{
  m_matrix = theInitialMatrix;
  m_preprocessFlag = shouldPreprocess;

  //Get the number of legal values for all cells in the matrix if preprocessing.
  if (m_preprocessFlag)
  {
    for (size_t i = 0; i < 9; i++)
    {
      for (size_t j = 0; j < 9; j++)
      {
        std::pair<int, int> possiblitiesForCell;
        possiblitiesForCell.first = m_matrix.GetPossibleValues(i, j).size();
        possiblitiesForCell.second = i * 9 + j;
        m_permutatedIndices.push_back(possiblitiesForCell);
      }
    }
    //Order cells by fewest legal values.
    std::sort(m_permutatedIndices.begin(), m_permutatedIndices.end());
  }
  else
  {
    for (size_t i = 0; i < 9; i++)
    {
      for (size_t j = 0; j < 9; j++)
      {
        std::pair<int, int> possiblitiesForCell;
        possiblitiesForCell.first = 0;
        possiblitiesForCell.second = i * 9 + j;
        m_permutatedIndices.push_back(possiblitiesForCell);
      }
    }
  }
}

SudokuMatrix SudokuSolver::Solve()
{
  //PopulateMatrix() works recursively to fill in the matrix.
  PopulateMatrix(0);
  return m_matrix;
}

bool SudokuSolver::PopulateMatrix(size_t theIndex)
{
  //If the matrix has been fully populated then return true.
  //Note that SudokuMatrix is fully populated if and only if it is the solution.
  if (theIndex > 80)
  {
    return true;
  }
  
  size_t nextIndex = theIndex + 1;
  size_t row = (size_t) m_permutatedIndices[theIndex].second / 9;
  size_t col = m_permutatedIndices[theIndex].second % 9;

  //Move on to next cell if the current one already has a value.
  if (m_matrix.GetValue(row, col) != SudokuMatrix::EMPTY_VALUE)
  {
    return PopulateMatrix(nextIndex);
  }

  //Loop through all values. SetValue() will only return true for values that
  //are legal for that cell. 
  for (size_t value = 1; value < 10; value++)
  {
    if (m_matrix.SetValue(row, col, value)
      && PopulateMatrix(nextIndex)
      )
    {
      return true;
    }
  }

  //If none of the legal values lead to the solution then clear the cell and return false.
  //This will result in the level above trying a new value for its cell and consequently a 
  //new set of legal values for other cells. 
  m_matrix.ClearValue(row, col);
  return false;
}

SudokuMatrix SudokuSolver::GetSolutionMatrix()
{
  return m_matrix;
}