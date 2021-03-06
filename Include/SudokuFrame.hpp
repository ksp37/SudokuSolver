#ifndef __SudokuFrame__
#define __SudokuFrame__

/**
@file
Subclass of wxFB_SudokuFrame, which is generated by wxFormBuilder.
*/

#include "wxFB_SudokuFrame.h"
#include "SudokuGrid.hpp"

//// end generated include

/** Implementing wxFB_SudokuFrame */
class SudokuFrame : public wxFB_SudokuFrame
{
	protected:
		// Handlers for wxFB_SudokuFrame events.
		void OnSolve( wxCommandEvent& event );
		void OnClear( wxCommandEvent& event );
	public:
		/** Constructor */
		SudokuFrame( wxWindow* parent );
    ~SudokuFrame();

protected:
  SudokuGrid * m_sudokuGrid;

	//// end generated class members
	
};

#endif // __SudokuFrame__
