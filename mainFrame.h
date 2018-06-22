// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

class wxMainFrame : public wxFrame
{
public:
    wxMainFrame(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size, long style);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSetting(wxCommandEvent& event);
    
    void OnInput(wxCommandEvent& event);
    void OnMaxlen(wxCommandEvent& event);
    
    void OnVersionC5401(wxCommandEvent& event);
    void OnVersionW9598(wxCommandEvent& event);
    void OnVersionNT4(wxCommandEvent& event);
    void OnVersionU20(wxCommandEvent& event);
	void OnVersionU31(wxCommandEvent& event);
    void OnVersionSISO(wxCommandEvent& event);
    
    void OnTimer(wxTimerEvent& event);
    
private:
    void InitialTable(int version);	       

    wxTextCtrl *inputtext;
    wxTextCtrl *resulttext;   
    
    wxTimer m_timer;
    
    DECLARE_EVENT_TABLE()
};


enum
{
    // menu items
    MENU_FILE_QUIT = wxID_EXIT,
    MENU_HELP_ABOUT = wxID_ABOUT,
    MENU_TOOL_SETTING,
    MENU_VERSION_C5401,
    MENU_VERSION_W9598,
    MENU_VERSION_NT4,
    MENU_VERSION_UC20,
	MENU_VERSION_UC31,
    MENU_VERSION_SISO,
    
    MAIN_INPUTTEXT,
    MAIN_RESULTTEXT,	
    
    MY_TIMER    
};
