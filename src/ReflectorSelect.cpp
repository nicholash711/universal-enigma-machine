#include <appcomponents/ReflectorSelect.h>
#include <appcomponents/MainFrame.h>

ReflectorSelect::ReflectorSelect(wxWindow* parent, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize) :
    wxComboBox(parent, ID_REFLECTOR_SELECTOR, "", pos, size, {}, wxCB_READONLY)
{
    this->Bind(wxEVT_COMBOBOX, OnChoose, this);
}

ReflectorSelect::~ReflectorSelect()
{
    
}

void ReflectorSelect::loadReflectors(std::vector<std::string> reflectors)
{
    std::vector<wxString> names;
    names.resize(reflectors.size());
    std::transform(reflectors.begin(), reflectors.end(), names.begin(), [](std::string str){
        wxString name(str);
        return name;
    });
    this->Set(names);
    this->SetSelection(0);
    MainFrame* frame = wxDynamicCast(GetParent(), MainFrame);
    std::array<std::string, 2> values = frame->getFile()->loadReflector(std::string(GetValue()));
    Reflector temp(values[0], values[1]);
    frame->getEnigma()->setReflector(temp);
    frame->getEnigma()->getReflector()->setRotatable(frame->getFile()->UKWRotate(frame->getModel()));
}

void ReflectorSelect::OnChoose(wxCommandEvent& event)
{
    MainFrame* frame = wxDynamicCast(GetParent(), MainFrame);
    std::array<std::string, 2> values = frame->getFile()->loadReflector(std::string(GetValue()));
    Reflector temp(values[0], values[1]);
    frame->getEnigma()->setReflector(temp);
    frame->getEnigma()->getReflector()->setRotatable(frame->getFile()->UKWRotate(frame->getModel()));
    frame->update();
}