#include "aboutDialog.h"

///////////////////////////////////////////////////////////////////////////

aboutDialog::aboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, 
		          const wxPoint& pos, const wxSize& size, long style, 
			  const wxString&name ) 
	: wxDialog( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Everyone is permitted to copy, modify and distribute verbatim copies of this program and its source code.  And this program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY.\n\nThis program is written by Danilo Chang, using cross-platform GUI library, wxWidgets.\n\nThanks for your use."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer1->Add( m_staticText1, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 10 );
	
	m_button1 = new wxButton( this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_button1, 0, wxALIGN_RIGHT|wxALL, 10 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
}
