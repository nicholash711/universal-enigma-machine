#ifndef ROTORSELECT_H
#define ROTORSELECT_H

#include <wx/wx.h>
#include <enigma/Rotor.h>
#include <vector>

class RotorSelect : public wxComboBox
{
    public:
        RotorSelect(wxWindow* parent, int i, const wxPoint &pos, const wxSize &size);
        ~RotorSelect();
        void loadChoices(std::vector<std::string> rotors);

    private:
        int rotor;
        void OnChoose(wxCommandEvent& event); 
};
enum
{
    ID_ROTOR_SELECTOR = 200
};

#endif