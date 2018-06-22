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
 * Copyright (c) 2007-2018 Danny Chang
 */
#ifdef __GNUG__
  #pragma implementation "app.h"
#endif

#include "app.h"
#include <wx/intl.h>
#include <wx/snglinst.h>
	
//for config
#include <wx/log.h>
#include <wx/config.h>
#include <wx/fileconf.h>
	
#include "mainFrame.h"
#include "tool.h"

CApp::CApp()
{
}

CApp::~CApp()
{
}

IMPLEMENT_APP(CApp);

wxLocale locale;

bool CApp::OnInit()
{
#ifdef __WXMSW__
  const wxString name = wxString::Format(_T("Array-%s"), wxGetUserId().c_str());
  wxSingleInstanceChecker *m_checker = new wxSingleInstanceChecker(name);
  
  if ( m_checker->IsAnotherRunning() )
  {
    wxLogError(_("Another program instance is already running, aborting."));

    return false;
  }
#endif

  locale.Init( _T("zh_TW.UTF-8"));
  wxLocale::AddCatalogLookupPathPrefix(wxT("."));
  wxLocale::AddCatalogLookupPathPrefix(wxT(".."));
  locale.AddCatalog(wxT("arraycode"));
  
  wxFileConfig *pConfig = new wxFileConfig(_T("arraycode.conf"));
  wxConfigBase::Set(pConfig);
    
  frame = new wxMainFrame((wxFrame *) NULL, _("Array30 Code Program"), wxPoint(1, 1), wxSize(520, 500), 
		  wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN);

  frame->Centre();
  frame->Show(true);

  return true;
}

int CApp::OnExit()
{
  delete wxConfigBase::Set((wxConfigBase *) NULL);
  return 0;
}
