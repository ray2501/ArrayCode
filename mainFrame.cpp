/*!
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 *
 * Everyone is permitted to copy, modify and distribute verbatim
 * copies of this program and its source code.
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General
 * Public Licence as published by the Free Software Foundation;
 * either version 2 of the Licence, or (at your option) any later
 * version.
 *
 * Copyright (c) 2007-2018  Danilo Chang
 */
#include <map>

#include <wx/intl.h>
#include <wx/ffile.h>

#include <wx/clipbrd.h>
	
//for config
#include <wx/log.h>
#include <wx/config.h>
#include <wx/fileconf.h>

#include "mainFrame.h"
#include "setdlg.h"
#include "aboutDialog.h"
#include "tool.h"
// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "myicon.xpm"
#endif 

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(wxMainFrame, wxFrame)
    EVT_MENU(MENU_FILE_QUIT,  wxMainFrame::OnQuit)
    EVT_MENU(MENU_VERSION_C5401, wxMainFrame::OnVersionC5401)
    EVT_MENU(MENU_VERSION_W9598, wxMainFrame::OnVersionW9598)
    EVT_MENU(MENU_VERSION_NT4, wxMainFrame::OnVersionNT4)
    EVT_MENU(MENU_VERSION_UC20, wxMainFrame::OnVersionU20)
    EVT_MENU(MENU_VERSION_UC31, wxMainFrame::OnVersionU31)
    EVT_MENU(MENU_VERSION_SISO, wxMainFrame::OnVersionSISO)     
    EVT_MENU(MENU_TOOL_SETTING, wxMainFrame::OnSetting) 
    EVT_MENU(MENU_HELP_ABOUT, wxMainFrame::OnAbout)
    
    EVT_TEXT(MAIN_INPUTTEXT, wxMainFrame::OnInput) 
    EVT_TEXT_MAXLEN(MAIN_INPUTTEXT, wxMainFrame::OnMaxlen)   
    
    EVT_TIMER(MY_TIMER, wxMainFrame::OnTimer)   	
END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// Global value
// ----------------------------------------------------------------------------
std::multimap<wxString, wxString> aTable;

const int C5401 = 0;
const int W9598 = 1;
const int NT4 = 2;
const int UNICODE20 = 3;
const int UNICODE31= 4;
const int SISO = 6;


// ----------------------------------------------------------------------------
// Implement
// ----------------------------------------------------------------------------
wxMainFrame::wxMainFrame(wxFrame *frame, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
  wxFrame(frame, wxID_ANY, title, pos, size, style)
{
    // set the frame icon
    SetIcon(wxICON(myicon));    
            
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(MENU_FILE_QUIT, _("Exit\tAlt-X"), _("Close this program"));
    
    wxMenu *versionMenu = new wxMenu;
    versionMenu->Append(MENU_VERSION_C5401, _("5401 Word"), _("5401 Word"));    
    versionMenu->Append(MENU_VERSION_W9598, _("Windows 95/98"), _("Windows 95/98"));    
    versionMenu->Append(MENU_VERSION_NT4, _("Windows NT4.0"), _("Windows NT4.0"));    
    versionMenu->Append(MENU_VERSION_UC20, _("Unicode 2.0"), _("Unicode 2.0"));    
	versionMenu->Append(MENU_VERSION_UC31, _("Unicode 3.1"), _("Unicode 3.1"));    
    versionMenu->Append(MENU_VERSION_SISO, _("Simplied"), _("Simplied"));    
    
    wxMenu *toolMenu = new wxMenu;
    toolMenu->Append(MENU_TOOL_SETTING, _("Setting"), _("Setup default version"));    
	
	wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(MENU_HELP_ABOUT, _("About"), _("About this program"));    
        
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _("File(&F)"));    
    menuBar->Append(versionMenu, _("Version(&V)"));
    menuBar->Append(toolMenu, _("Tool(&T)"));    
	menuBar->Append(helpMenu, _("Help(&H)"));    

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
    
    wxBoxSizer *mainsizer;
    mainsizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *upsizer;
    upsizer = new wxBoxSizer(wxVERTICAL);
    inputtext = new wxTextCtrl(this, MAIN_INPUTTEXT,wxT(""),wxDefaultPosition, wxSize(370, 25),0);
    inputtext->SetMaxLength(100);
    inputtext->SetFocus();
    upsizer->Add(inputtext, 0, wxLEFT, 1);    
    mainsizer->Add(upsizer, 0, wxLEFT, 1);
    
    resulttext = new wxTextCtrl(this, MAIN_RESULTTEXT,wxT(""),wxDefaultPosition,wxDefaultSize, 
		        wxTE_MULTILINE | wxTE_READONLY );
    mainsizer->Add(resulttext, 1, wxLEFT|wxEXPAND, 1);
    this->SetSizer(mainsizer);
    this->SetAutoLayout(true);
    this->Layout();    
    
    // set Status Bar
    CreateStatusBar(2);
    SetStatusText(_("Welcome!"));
    
    wxConfigBase *pConfig = wxConfigBase::Get();    
	pConfig->SetPath(_T("/Type"));    
	int version = pConfig->Read(_T("Version"), UNICODE31);
	InitialTable(version);
            
    m_timer.SetOwner(this, MY_TIMER);
    m_timer.Start(1000);    // 1 second interval

	inputtext->SetFocus();
}

void wxMainFrame::InitialTable(int version)
{
    // Initial: Get the code data
    wxTextFile file;
    
    wxString path = wxPathOnly(::GetExecutablePath());    

	if(version==C5401) {
		path = path + wxT("/array30_5401.txt");
		file.Open(path);
	} else if(version==W9598) {
		path = path + wxT("/array30_w9598.txt");
    	file.Open(path);
    } else if(version==NT4) {
    	path = path + wxT("/array30_nt4.txt");
    	file.Open(path);
	} else if(version==UNICODE20) {
		path = path + wxT("/array30_u20.txt");
    	file.Open(path);
    } else if(version==UNICODE31) {
		path = path + wxT("/array30_u31.txt");
    	file.Open(path);
    } else if(version==SISO) {
    	path = path + wxT("/array30_siso.txt");
    	file.Open(path);
    } else {
    	path = path + wxT("/array30_u20.txt");
    	file.Open(path);
    }

    for (wxString str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine() )
    {
		bool bIsCode = true;
		int count = 0;
		int length = str.length();
		
		if(length < 1)
			continue;
		
		wxChar codeBuffer[8] = {0};
		wxChar wordBuffer[4] = {0};
		
		while(str[count])
		{
			if(str[count]==L' ' || str[count]==L'\t')
			{
				bIsCode = false;		
				count++;
			
				continue;
			}
				
			if(bIsCode)
				codeBuffer[count] = str[count];
			else
				wordBuffer[length - count - 1] = str[count];
				
			// Open Watcom need declare const, let OW happy.
			wxString word = wordBuffer;
			wxString code = codeBuffer;
			std::pair<const wxString, wxString> mapping(word, code);
			aTable.insert(mapping); 
			
			count++;
		}
    }	
}



/*********************************************************************
 * Event Handler here.
 * Put the event function below.
 *********************************************************************/
void wxMainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}


void wxMainFrame::OnSetting(wxCommandEvent& event)
{
    setDialog *dlg = new setDialog(this, ID_DEFAULT, _("Setup default version"));    
        
    if ( dlg->ShowModal() == wxID_OK ) {    	
	int defaultvalue;
	wxString value = dlg->m_comboBox->GetValue();
	if(value.Contains(_("5401 Word")))
		defaultvalue = C5401;
	else if(value.Contains(_("Windows 95/98")))
		defaultvalue = W9598;
	else if(value.Contains(_("Windows NT4.0")))
		defaultvalue = NT4;
	else if(value.Contains(_("Unicode 2.0")))
		defaultvalue = UNICODE20;
	else if(value.Contains(_("Unicode 3.1")))
		defaultvalue = UNICODE31;
	else if(value.Contains(_("Simplied")))
		defaultvalue = SISO;
	else
		defaultvalue = UNICODE20;

	wxConfigBase *pConfig = wxConfigBase::Get();    
	pConfig->SetPath(_T("/Type"));  
	pConfig->Write(_T("Version"), defaultvalue);

	dlg->Destroy();
   }
}

void wxMainFrame::OnVersionC5401(wxCommandEvent& WXUNUSED(event))
{
    aTable.clear();
    
    InitialTable(C5401);
}


void wxMainFrame::OnVersionW9598(wxCommandEvent& WXUNUSED(event))
{
    aTable.clear();
    
    InitialTable(W9598);
}


void wxMainFrame::OnVersionNT4(wxCommandEvent& WXUNUSED(event))
{
    aTable.clear();
    
    InitialTable(NT4);
}


void wxMainFrame::OnVersionU20(wxCommandEvent& WXUNUSED(event))
{
    aTable.clear();
    
    InitialTable(UNICODE20);
}

void wxMainFrame::OnVersionU31(wxCommandEvent& WXUNUSED(event))
{
    aTable.clear();
    
    InitialTable(UNICODE31);
}


void wxMainFrame::OnVersionSISO(wxCommandEvent& WXUNUSED(event))
{
    aTable.clear();
    
    InitialTable(SISO);
}


void wxMainFrame::OnInput(wxCommandEvent& WXUNUSED(event))
{
    resulttext->Clear();
    bool isUnicode31word = false;
    // Clear TextCtrl test	
	
    wxString text = inputtext->GetValue();
    if(text.IsEmpty() == true)
    	return;    	

// For Unicode 3.1, need special handle surrogate area char
    wxString value, value2;
	
	if(text.Last() >= 0xDC00 && text.Last() <= 0xDFFF)
	{
		isUnicode31word = true;

		value += wxString(text[text.Len() - 2]);
		value += wxString(text.Last());

		value2 += wxString(text.Last());
		value2 += wxString(text[text.Len() - 2]);
	}
	else
	{
		value += wxString(text.Last());

		value2 += wxString(text.Last());
	}
    	
    std::multimap<wxString, wxString>::iterator pos;    
    wxString showme;
    
    resulttext->AppendText(_("Result: ") + value + _T("\n\n")); 

    for(pos = aTable.find(value2); pos != aTable.end(); ++pos) {
    	if(pos->first==value2) {    	

   		showme = pos->second;
		showme = showme.Upper();

    		showme.Replace(_T("Q"), _T("1^ "), true);
    		showme.Replace(_T("A"), _T("1- "), true);
    		showme.Replace(_T("Z"), _T("1v "), true);
    		showme.Replace(_T("W"), _T("2^ "), true);
    		showme.Replace(_T("S"), _T("2- "), true);
    		showme.Replace(_T("X"), _T("2v "), true);
    		showme.Replace(_T("E"), _T("3^ "), true);
    		showme.Replace(_T("D"), _T("3- "), true);
    		showme.Replace(_T("C"), _T("3v "), true);
    		showme.Replace(_T("R"), _T("4^ "), true);
    		showme.Replace(_T("F"), _T("4- "), true);
    		showme.Replace(_T("V"), _T("4v "), true);
    		showme.Replace(_T("T"), _T("5^ "), true);
    		showme.Replace(_T("G"), _T("5- "), true);
    		showme.Replace(_T("B"), _T("5v "), true);
    		showme.Replace(_T("Y"), _T("6^ "), true);
    		showme.Replace(_T("H"), _T("6- "), true);
    		showme.Replace(_T("N"), _T("6v "), true);
    		showme.Replace(_T("U"), _T("7^ "), true);
    		showme.Replace(_T("J"), _T("7- "), true);
    		showme.Replace(_T("M"), _T("7v "), true);
    		showme.Replace(_T("I"), _T("8^ "), true);
    		showme.Replace(_T("K"), _T("8- "), true);
    		showme.Replace(_T(","), _T("8v "), true);
    		showme.Replace(_T("O"), _T("9^ "), true);
    		showme.Replace(_T("L"), _T("9- "), true);
    		showme.Replace(_T("."), _T("9v "), true);
    		showme.Replace(_T("P"), _T("0^ "), true);
    		showme.Replace(_T(";"), _T("0- "), true);
    		showme.Replace(_T("/"), _T("0v "), true);
    		// replace the the array code mapping
    		
    		resulttext->AppendText(_T("(") + showme + _T(")") + _T("\n"));    		
	} 
    } 
    
    resulttext->AppendText(_("\n"));    
#if (__WXMSW__)
if(isUnicode31word==false)
{
	WCHAR wstring[63];
	wcscpy(wstring, value.c_str());
	WCHAR **outptr = NULL;
	outptr = GetConversionList(_T("winar30.ime"), wstring);

	if(outptr)
	{
		resulttext->AppendText(_("\nNow search Array30 IME:\n\n"));    

		for(int i = 0; outptr[i] != NULL; i++)
		{
			resulttext->AppendText(_T("(") + wxString(outptr[i]) + _T(")") + _T("\n")); 
		}

		for(int i = 0;outptr[i] != NULL; i++)
		{
			if(outptr[i]) free(outptr[i]);
		}

		free(outptr);
		outptr = NULL;
	}

	outptr = GetConversionList(_T("phon.ime"), wstring);

	if(outptr)
	{
		resulttext->AppendText(_("\nNow search Phon IME:\n\n"));    

		for(int i = 0; outptr[i] != NULL; i++)
		{
			resulttext->AppendText(_T("(") + wxString(outptr[i]) + _T(")") + _T("\n")); 
		}

		for(int i = 0;outptr[i] != NULL; i++)
		{
			if(outptr[i]) free(outptr[i]);
		}

		free(outptr);
		outptr = NULL;
	}
}
#endif
}


void wxMainFrame::OnMaxlen(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _("Warning: You could only input 50 word!"));

    wxMessageBox(msg, _("Error"), wxOK | wxICON_ERROR, this);
}


void wxMainFrame::OnAbout(wxCommandEvent& event)
{
    aboutDialog *dlg = new aboutDialog(this, ID_DEFAULT, _("About"));    
        
    if ( dlg->ShowModal() == wxID_OK ) {    	
        // Do nothing
    }
}


void wxMainFrame::OnTimer(wxTimerEvent& WXUNUSED(event))
{
    wxString msg = ::wxNow();    
    
    SetStatusText(msg, 1);
}


