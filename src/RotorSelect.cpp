#include <appcomponents/RotorSelect.h>

RotorSelect::RotorSelect(wxWindow* parent, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize) :
    wxComboBox(parent, ID_ROTOR_SELECTOR, "", pos, size)
{
    this->Bind(wxEVT_COMBOBOX, OnChoose, this);
}

RotorSelect::~RotorSelect()
{

}

void RotorSelect::loadChoices(std::string selects[])
{

}

void RotorSelect::OnChoose(wxCommandEvent& event)
{
    
}