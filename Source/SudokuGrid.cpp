#include <wx/pen.h>
#include "SudokuGrid.hpp"
#include <wx/spinctrl.h>


SudokuGrid::SudokuGrid(wxWindow * theParent, int theCellSize)
  : wxGrid(theParent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0)
{
  //Sets the number range allowed on a grid cell.

  SetDefaultEditor(new wxGridCellNumberEditor(1, 9));
  // Grid
  CreateGrid(9, 9);
  EnableEditing(true);
  EnableGridLines(true);
  EnableDragGridSize(false);
  SetMargins(0, 0);

  // Columns
  wxGridSizesInfo cellSizes;
  cellSizes.m_sizeDefault = 40;
  SetColSizes(cellSizes);
  SetRowSizes(cellSizes);

  EnableDragColMove(false);
  EnableDragColSize(true);
  SetColLabelSize(0);
  SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
  EnableDragRowSize(true);
  SetRowLabelSize(0);

  Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(SudokuGrid::OnDelete), NULL, this);
}

wxPen SudokuGrid::GetColGridLinePen(int theCol)
{
  if (theCol == 2 || theCol == 5)
  {
    return wxPen(wxColour(0, 0, 0), 3);
  }
  else
  {
    return wxPen(wxColour(0, 0, 0), 1);
  }
}

wxPen SudokuGrid::GetRowGridLinePen(int theRow)
{
  if (theRow == 2 || theRow == 5)
  {
    return wxPen(wxColour(0, 0, 0), 3);
  }
  else
  {
    return wxPen(wxColour(0, 0, 0), 1);
  }
}

void SudokuGrid::OnDelete(wxKeyEvent & event)
{
  int key = event.GetKeyCode();

  if (key == WXK_DELETE)
  {
    int selectedCellRow = GetGridCursorRow();
    int selectedCellCol = GetGridCursorCol();
    SetCellValue(selectedCellRow, selectedCellCol, "");
  }

  event.Skip();
}