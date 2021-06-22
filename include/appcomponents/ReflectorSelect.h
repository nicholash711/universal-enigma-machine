#ifndef REFLECTORSELECT_H
#define REFLECTORSELECT_H

#include <wx/wx.h>

class ReflectorSelect : public wxComboBox
{
    public:
        ReflectorSelect(wxWindow* parent, const wxPoint &pos, const wxSize &size);
        ~ReflectorSelect();
        void loadReflectors();

    private:
        void OnChoose(wxCommandEvent& event);
};
enum
{
    ID_REFLECTOR_SELECTOR = 400
};
#endif