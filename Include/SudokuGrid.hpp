#ifndef SUDOKU_GRID
#define SUDOKU_GRID

#include <wx/grid.h>

class SudokuGrid : public wxGrid
{
  public:
    
    SudokuGrid(wxWindow * theParent, int theCellSize);

    wxPen GetColGridLinePen(int theCol);
    wxPen GetRowGridLinePen(int theCol);

};

#endif //SUDOKU_GRID