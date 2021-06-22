#include <appcomponents/RotorSelect.h>

RotorSelect::RotorSelect(wxWindow* parent, Rotor* rotor, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize) :
    wxComboBox(parent, ID_ROTOR_SELECTOR, "", pos, size)
{
    this->Bind(wxEVT_COMBOBOX, OnChoose, this);
    this->rotor = rotor;
}

RotorSelect::~RotorSelect()
{

}

void RotorSelect::loadChoices(std::vector<std::string> rotors)
{
    std::vector<wxString> names;
    names.resize(rotors.size());
    std::transform(rotors.begin(), rotors.end(), names.begin(), [](std::string str){
        wxString name(str);
        return name;
    });
    this->Set(names);
    this->SetSelection(0);
}

void RotorSelect::OnChoose(wxCommandEvent& event)
{
    
}