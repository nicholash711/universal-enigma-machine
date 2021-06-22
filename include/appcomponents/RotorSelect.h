#ifndef ROTORSELECT_H
#define ROTORSELECT_H

#include <wx/wx.h>
#include <enigma/Rotor.h>
#include <vector>

class RotorSelect : public wxComboBox
{
    public:
        RotorSelect(wxWindow* parent, const wxPoint &pos, const wxSize &size, Rotor* rotor);
        ~RotorSelect();
        void loadChoices(std::vector<std::string> rotors);

    private:
        Rotor* rotor = nullptr;
        void OnChoose(wxCommandEvent& event); 
};
enum
{
    ID_ROTOR_SELECTOR = 200
};

#endif