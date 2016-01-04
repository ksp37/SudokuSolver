#include "SudokuFrame.hpp"
#include "SudokuSolver.hpp"
#include <wx/msgdlg.h>

SudokuFrame::SudokuFrame( wxWindow* parent )
:
wxFB_SudokuFrame( parent )
{
  m_sudokuGrid = new SudokuGrid(this, 9);
  m_gridSizer->Add(m_sudokuGrid, 0, wxALL, 10);
  Layout();
}

SudokuFrame::~SudokuFrame()
{
  delete m_sudokuGrid;
}


void SudokuFrame::OnSolve( wxCommandEvent& event )
{
  size_t noCols = m_sudokuGrid->GetNumberCols();
  size_t noRows = m_sudokuGrid->GetNumberRows();
  SudokuMatrix matrix;

  for (size_t i = 0; i < noRows; i++)
  {
    for (size_t j = 0; j < noCols; j++)
    {
      wxString strValue = m_sudokuGrid->GetCellValue(i, j);
      long value;
      if (strValue.ToLong(&value))
      {
        if (!matrix.SetValue(i, j, value))
        {
          wxMessageDialog dlg(this, "The sudoku entered is invalid!");
          dlg.ShowModal();
          return;
        }
      }
    }
  }

  SudokuSolver solver(matrix, true);
  SudokuMatrix solutionMatrix = solver.Solve();

  for (size_t i = 0; i < noRows; i++)
  {
    for (size_t j = 0; j < noCols; j++)
    {
      int value;
      if (m_sudokuGrid->GetCellValue(i, j).IsEmpty()
        && (value = solutionMatrix.GetValue(i, j)) != SudokuMatrix::OUT_OF_BOUNDS
        )
      {
        wxString valueStr = wxString::Format(wxT("%i"), value);
        m_sudokuGrid->SetCellTextColour(i, j, wxColour(255, 0, 0));
        m_sudokuGrid->SetCellValue(valueStr, i, j);
      }
    }
  }

  m_sudokuGrid->EnableEditing(false);
}

void SudokuFrame::OnClear( wxCommandEvent& event )
{
  m_sudokuGrid->ClearGrid();
  size_t noCols = m_sudokuGrid->GetNumberCols();
  size_t noRows = m_sudokuGrid->GetNumberRows();

  for (size_t i = 0; i < noRows; i++)
  {
    for (size_t j = 0; j < noCols; j++)
    {
      m_sudokuGrid->SetCellTextColour(i, j, wxColour(0, 0, 0));
    }
  }

  m_sudokuGrid->EnableEditing(true);
}
