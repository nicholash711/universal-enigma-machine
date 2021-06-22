#ifndef ENTRYWHEELSELECT_H
#define ENTRYWHEELSELECT_H

#include <wx/wx.h>
#include <enigma/EntryWheel.h>
#include <vector>

class EntryWheelSelect : public wxComboBox
{
    public:
        EntryWheelSelect(wxWindow* parent, EntryWheel* wheel, const wxPoint &pos, const wxSize &size);
        ~EntryWheelSelect();
        void loadEntryWheel(std::vector<std::string> wheels);

    private:
        EntryWheel* wheel;
        void OnChoose(wxCommandEvent& event);
};
enum
{
    ID_ENTRYWHEEL_SELECTOR = 600
};
#endif