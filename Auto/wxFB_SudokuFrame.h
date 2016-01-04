///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __wxFB_SudokuFrame__
#define __wxFB_SudokuFrame__

#include <wx/sizer.h>
#include <wx/gdicmn.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class wxFB_SudokuFrame
///////////////////////////////////////////////////////////////////////////////
class wxFB_SudokuFrame : public wxFrame 
{
	private:
	
	protected:
		wxBoxSizer* m_gridSizer;
		wxButton* m_solveBtn;
		
		wxButton* m_clearBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSolve( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClear( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		wxFB_SudokuFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Sudoku Solver"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCLIP_CHILDREN );
		~wxFB_SudokuFrame();
	
};

#endif //__wxFB_SudokuFrame__
