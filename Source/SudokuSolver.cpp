#include "SudokuSolver.hpp"
#include <map>

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
  }
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

bool SudokuMatrix::IsValueWithinRange(int theValue) const
{
  return (theValue < 10 && theValue > 0) || theValue == EMPTY_VALUE;
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