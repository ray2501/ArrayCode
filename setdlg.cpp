#include "setdlg.h"

setDialog::setDialog(wxWindow *parent, int id, wxString title) : 
	wxDialog(parent, id, title, wxDefaultPosition, wxSize(390,125))
{
  wxBoxSizer *bSizer1;
  bSizer1 = new wxBoxSizer(wxVERTICAL);
  m_comboBox = new wxComboBox(this, ID_DEFAULT, _T("Unicode 3.1"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
  m_comboBox->Append(_T("5401 Word"));
  m_comboBox->Append(_T("Windows 95/98"));
  m_comboBox->Append(_T("Windows NT4.0"));
  m_comboBox->Append(_T("Unicode 2.0"));
  m_comboBox->Append(_T("Unicode 3.1"));
  m_comboBox->Append(_T("Simplied"));
  
  m_comboBox->SetValue(_T("Unicode 3.1"));
       
  bSizer1->Add(m_comboBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_BOTTOM|wxEXPAND, 5);
  m_button = new wxButton(this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0);
       
  bSizer1->Add(m_button, 0, wxALL|wxALIGN_RIGHT, 5);
  this->SetSizer(bSizer1);
  this->SetAutoLayout(true);
  this->Layout();
}

