#include "SudokuSolver.hpp"
#include <algorithm>
#include <functional>

Matrix::Matrix(size_t theRowSize, size_t theColSize)
{
  for (size_t i = 0; i < theRowSize; i++)
  {
    m_vectorMatrix.push_back(std::vector<size_t>(theColSize, 0));
  }
}

int Matrix::GetValue(size_t theRow, size_t theCol) const
{
  if (theRow < m_vectorMatrix.size() && theCol < m_vectorMatrix[theRow].size())
  {
    return m_vectorMatrix[theRow][theCol];
  }
  else
  {
    //TODO: Need to return appropriate error value here (NOT -1!)
    return -1;
  }
}

bool Matrix::SetValue(size_t theRow, size_t theCol, int theValue)
{
  if (theRow < m_vectorMatrix.size() && theCol < m_vectorMatrix[theRow].size())
  {
    m_vectorMatrix[theRow][theCol] = theValue;
    return true;
  }
  else
  {
    return false;
  }
}

size_t Matrix::GetColSize(size_t theCol) const 
{
  return m_vectorMatrix.size();
}


size_t Matrix::GetRowSize(size_t theRow) const
{
  return m_vectorMatrix.size() == 0 ? 0 : m_vectorMatrix[0].size();
}



//-----------------------------------------------------------------------------------------------//


SudokuMatrix::SudokuMatrix()
{
  for (size_t i = 0; i < 9; i++)
  {
    m_vectorMatrix.push_back(std::vector<size_t>(9, EMPTY_VALUE));
    m_possibleValuesSet.insert(i + 1);
  }

  m_possibleValuesSet.insert(EMPTY_VALUE);
}


int SudokuMatrix::GetValue(size_t theRow, size_t theCol) const
{
  if (theRow < m_vectorMatrix.size() && theCol < m_vectorMatrix[theRow].size())
  {
    return m_vectorMatrix[theRow][theCol];
  }
  else
  {
    return -1;
  }
}

bool SudokuMatrix::SetValue(size_t theRow, size_t theCol, int theValue)
{
  if (theRow < m_vectorMatrix.size() 
    && theCol < m_vectorMatrix[theRow].size()
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
  if (theRow < m_vectorMatrix.size()
    && theCol < m_vectorMatrix[theRow].size()
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

  if ((blockRowStart + 1) * 3 >= m_vectorMatrix.size()
    || (blockColStart + 1) * 3 >= m_vectorMatrix[blockRowStart].size()
    || !IsValueWithinRange(theValue)
    )
  {
    // out of bounds or range error
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
  if (theRow >= m_vectorMatrix.size()
    || !IsValueWithinRange(theValue)
    )
  {
    // out of bounds or range error
    return false;
  }

  for (size_t i = 0, size = m_vectorMatrix[theRow].size(); i < size; i++)
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
  for (size_t i = 0, size = m_vectorMatrix.size(); i < size; i++)
  {
    if (theCol >= m_vectorMatrix[i].size() 
      || !IsValueWithinRange(theValue)
      )
    {
      // out of bounds or range error
      return false;
    }
  }

  for (size_t i = 0, size = m_vectorMatrix.size(); i < size; i++)
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

  if (theRow >= m_vectorMatrix.size() || theCol >= m_vectorMatrix[theRow].size())
  {
    return remainingSet;
  }

  for (size_t i = blockRowStart * 3; i < (blockRowStart + 1) * 3; i++)
  {
    for (size_t j = blockColStart * 3; j < (blockColStart + 1) * 3; j++)
    {
      currentSet.insert(m_vectorMatrix[i][j]);
    }
  }

  for (size_t i = 0, size = m_vectorMatrix[theRow].size(); i < size; i++)
  {
    currentSet.insert(m_vectorMatrix[theRow][i]);
  }

  for (size_t i = 0, size = m_vectorMatrix.size(); i < size; i++)
  {
    currentSet.insert(m_vectorMatrix[i][theCol]);
  }

  std::set_difference(m_possibleValuesSet.begin(), m_possibleValuesSet.end(),
    currentSet.begin(), currentSet.end(),
    remainingSet.begin()
    );

  return remainingSet;
}

bool SudokuMatrix::IsSolved() const
{
  for (size_t i = 0, colSize = m_vectorMatrix.size(); i < colSize; i++)
  {
    for (size_t j = 0, rowSize = m_vectorMatrix[i].size(); j < rowSize; j++)
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
  }

  std::sort(m_permutatedIndices.begin(), m_permutatedIndices.end());

}

std::vector< std::vector<size_t> > SudokuSolver::Solve()
{
  //TODO
}

bool SudokuSolver::PopulateMatrix(size_t theRow, size_t theCol)
{
  //TODO
  //if (m_matrix.IsSolved())
  //{
  //  return true;
  //}

  //if (m_matrix.GetValue(theRow, theCol) != SudokuMatrix::EMPTY_VALUE)
  //{
  //  PopulateMatrix(theRow, theCol);
  //}

  //for (size_t value = 0; value < 10; value++)
  //{
  //  if (!m_matrix.SetValue(theRow, theCol, value)
  //    || !PopulateMatrix(theRow, theCol)
  //    )
  //  {
  //    continue;
  //  }
  //}
  //m_matrix.SetValue(theRow, theCol, 0);
  //return false;
}

const std::vector< std::vector<size_t> > & SudokuSolver::GetSolutionMatrix()
{
  //TODO
}