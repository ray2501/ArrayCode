#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

class aboutDialog : public wxDialog
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxButton* m_button1;
	
	public:
		aboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, 
		             const wxString& title = wxEmptyString, 
			     const wxPoint& pos = wxDefaultPosition, 
			     const wxSize& size = wxSize( 345,285 ), 
			     long style = wxDEFAULT_DIALOG_STYLE,
			     const wxString& name = wxDialogNameStr );
	
};

