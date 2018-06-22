#ifndef APP_H
#define APP_H

#ifdef __GNUG__
  #pragma interface "app.h"
#endif

#include <wx/wx.h> // inheriting class's header file

class wxMainFrame;

class CApp : public wxApp
{
public:
	CApp();
	~CApp();
	virtual bool OnInit();
	int OnExit();
    
    wxMainFrame *frame;
};

DECLARE_APP(CApp)

#endif // APP_H
