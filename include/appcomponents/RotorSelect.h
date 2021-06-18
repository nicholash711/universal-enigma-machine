#ifndef ROTORSELECT_H
#define ROTORSELECT_H

#include <wx/wx.h>

class RotorSelect : public wxComboBox
{
    public:
        RotorSelect(wxWindow* parent, const wxPoint &pos, const wxSize &size);
        ~RotorSelect();
        void loadChoices(std::string selects[]);

    private:
        void OnChoose(wxCommandEvent& event); 
};
enum
{
    ID_ROTOR_SELECTOR = 200
};

#endif