#ifndef SUDOKU_GRID
#define SUDOKU_GRID

#include <wx/grid.h>

class SudokuGrid : public wxGrid
{
  public:
    
    SudokuGrid(wxWindow * theParent, int theCellSize);

    wxPen GetColGridLinePen(int theCol);
    wxPen GetRowGridLinePen(int theCol);

private:
  void OnDelete(wxKeyEvent & event);
};

#endif //SUDOKU_GRID