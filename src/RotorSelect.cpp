#include <appcomponents/RotorSelect.h>
#include <appcomponents/MainFrame.h>

RotorSelect::RotorSelect(wxWindow* parent, int i, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize) :
    wxComboBox(parent, ID_ROTOR_SELECTOR, "", pos, size, {}, wxCB_READONLY)
{
    this->Bind(wxEVT_COMBOBOX, OnChoose, this);
    rotor = i;
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
    int temp = frame->getEnigma()->isM4() ? rotor - 1 : rotor;
    if(temp >= 0)
    {
        std::array<std::string, 3> values = frame->getFile()->loadRotor(std::string(GetValue()));
        frame->getEnigma()->setRotor(values[0], values[1], values[2], temp);
    }
    else
    {
        std::array<std::string, 2> values4 = frame->getFile()->loadRotorFour(std::string(GetValue()));
        frame->getEnigma()->setRotor4(values4[0], values4[1]);
    }
}

void RotorSelect::OnChoose(wxCommandEvent& event)
{
    MainFrame* frame = wxDynamicCast(this->GetParent(), MainFrame);
    int temp = frame->getEnigma()->isM4() ? rotor - 1 : rotor;
    if(temp >= 0)
    {
        std::array<std::string, 3> values = frame->getFile()->loadRotor(std::string(GetValue()));
        frame->getEnigma()->setRotor(values[0], values[1], values[2], temp);
    }
    else
    {
        std::array<std::string, 2> values4 = frame->getFile()->loadRotorFour(std::string(GetValue()));
        frame->getEnigma()->setRotor4(values4[0], values4[1]);
    }
    frame->updateRotor(temp);
    frame->update();
}