#include <appcomponents/EntryWheelSelect.h>

EntryWheelSelect::EntryWheelSelect(wxWindow* parent, const wxPoint &pos, const wxSize &size, EntryWheel* wheel) :
    wxComboBox(parent, ID_ENTRYWHEEL_SELECTOR, "", pos, size, {}, wxCB_READONLY)
{
    this->wheel = wheel;
}

EntryWheelSelect::~EntryWheelSelect()
{

}

void EntryWheelSelect::loadEntryWheel(std::vector<std::string> wheels)
{
    std::vector<wxString> names;
    names.resize(wheels.size());
    std::transform(wheels.begin(), wheels.end(), names.begin(), [](std::string str){
        wxString name(str);
        return name;
    });
    this->Set(names);
    this->SetSelection(0);
}