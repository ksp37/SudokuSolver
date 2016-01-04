///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wxFB_SudokuFrame.h"

///////////////////////////////////////////////////////////////////////////

wxFB_SudokuFrame::wxFB_SudokuFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,475 ), wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	wxBoxSizer* frameSizer;
	frameSizer = new wxBoxSizer( wxVERTICAL );
	
	m_gridSizer = new wxBoxSizer( wxVERTICAL );
	
	frameSizer->Add( m_gridSizer, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_solveBtn = new wxButton( this, wxID_ANY, wxT("Solve"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_solveBtn, 0, wxALL, 10 );
	
	
	buttonSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_clearBtn = new wxButton( this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_clearBtn, 0, wxALL, 10 );
	
	frameSizer->Add( buttonSizer, 0, wxEXPAND, 5 );
	
	this->SetSizer( frameSizer );
	this->Layout();
	frameSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_solveBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wxFB_SudokuFrame::OnSolve ), NULL, this );
	m_clearBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wxFB_SudokuFrame::OnClear ), NULL, this );
}

wxFB_SudokuFrame::~wxFB_SudokuFrame()
{
	// Disconnect Events
	m_solveBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wxFB_SudokuFrame::OnSolve ), NULL, this );
	m_clearBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( wxFB_SudokuFrame::OnClear ), NULL, this );
	
}
