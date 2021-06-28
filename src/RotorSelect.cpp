#include <appcomponents/RotorSelect.h>
#include <appcomponents/MainFrame.h>

RotorSelect::RotorSelect(wxWindow* parent, int i, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize) :
    wxComboBox(parent, ID_ROTOR_SELECTOR, "", pos, size)
{
    this->Bind(wxEVT_COMBOBOX, OnChoose, this);
    rotor = i + 1;
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
    MainFrame* frame = wxDynamicCast(GetParent(), MainFrame);
    // frame->OnRotorChoose(std::string(GetValue()), rotor);
    std::array<std::string, 3> values = frame->getFile()->loadRotor(std::string(GetValue()));
    Rotor temp(values[0], values[1], values[2]);
    frame->getEnigma()->setRotor(temp, rotor);
}

void RotorSelect::OnChoose(wxCommandEvent& event)
{
    MainFrame* frame = wxDynamicCast(this->GetParent(), MainFrame);
    // frame->OnRotorChoose(std::string(GetValue()), rotor);
    std::array<std::string, 3> values = frame->getFile()->loadRotor(std::string(GetValue()));
    Rotor temp(values[0], values[1], values[2]);
    frame->getEnigma()->setRotor(temp, rotor);
}