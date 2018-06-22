#include <wx/wx.h>
#include <wx/button.h>

#define ID_DEFAULT -1 // Default

class setDialog : public wxDialog
{
  private:
  
  protected:    
    wxButton *m_button;
  
  public:
  	wxComboBox *m_comboBox;
    
    setDialog(wxWindow *parent, int id = -1, wxString title = wxT("Setting"));
  
};

