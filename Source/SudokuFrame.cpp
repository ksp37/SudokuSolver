#include "SudokuFrame.hpp"

SudokuFrame::SudokuFrame( wxWindow* parent )
:
wxFB_SudokuFrame( parent )
{
  m_sudokuGrid = new SudokuGrid(this, 9);
  m_gridSizer->Add(m_sudokuGrid, 0, wxALL, 5);
}

SudokuFrame::~SudokuFrame()
{
  delete m_sudokuGrid;
}


void SudokuFrame::OnSolve( wxCommandEvent& event )
{
// TODO: Implement OnSolve
}

void SudokuFrame::OnClear( wxCommandEvent& event )
{
// TODO: Implement OnClear
}
