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
	
#include <wx/filename.h>

#ifdef __WXMSW__
#include <imm.h>
#endif

const wxString GetExecutablePath();

#ifdef __WXMSW__
WCHAR **GetConversionList(WCHAR *imefilename, WCHAR *instring);
#endif

