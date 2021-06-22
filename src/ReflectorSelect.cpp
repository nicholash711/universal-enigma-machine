#include <appcomponents/ReflectorSelect.h>

ReflectorSelect::ReflectorSelect(wxWindow* parent, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize) :
    wxComboBox(parent, ID_REFLECTOR_SELECTOR, "", pos, size)
{

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
}