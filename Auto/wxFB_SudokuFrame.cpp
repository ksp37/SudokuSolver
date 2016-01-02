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
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_sudokuGrid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_sudokuGrid->CreateGrid( 9, 9 );
	m_sudokuGrid->EnableEditing( true );
	m_sudokuGrid->EnableGridLines( true );
	m_sudokuGrid->EnableDragGridSize( false );
	m_sudokuGrid->SetMargins( 0, 0 );
	
	// Columns
	m_sudokuGrid->SetColSize( 0, 30 );
	m_sudokuGrid->SetColSize( 1, 30 );
	m_sudokuGrid->SetColSize( 2, 30 );
	m_sudokuGrid->SetColSize( 3, 30 );
	m_sudokuGrid->SetColSize( 4, 30 );
	m_sudokuGrid->SetColSize( 5, 30 );
	m_sudokuGrid->SetColSize( 6, 30 );
	m_sudokuGrid->SetColSize( 7, 30 );
	m_sudokuGrid->SetColSize( 8, 30 );
	m_sudokuGrid->EnableDragColMove( false );
	m_sudokuGrid->EnableDragColSize( true );
	m_sudokuGrid->SetColLabelSize( 0 );
	m_sudokuGrid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_sudokuGrid->SetRowSize( 0, 30 );
	m_sudokuGrid->SetRowSize( 1, 30 );
	m_sudokuGrid->SetRowSize( 2, 30 );
	m_sudokuGrid->SetRowSize( 3, 30 );
	m_sudokuGrid->SetRowSize( 4, 30 );
	m_sudokuGrid->SetRowSize( 5, 30 );
	m_sudokuGrid->SetRowSize( 6, 30 );
	m_sudokuGrid->SetRowSize( 7, 30 );
	m_sudokuGrid->SetRowSize( 8, 30 );
	m_sudokuGrid->EnableDragRowSize( true );
	m_sudokuGrid->SetRowLabelSize( 0 );
	m_sudokuGrid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_sudokuGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer1->Add( m_sudokuGrid, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_solveBtn = new wxButton( this, wxID_ANY, wxT("Solve"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_solveBtn, 0, wxALL, 5 );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_clearBtn = new wxButton( this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_clearBtn, 0, wxALL, 5 );
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
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
