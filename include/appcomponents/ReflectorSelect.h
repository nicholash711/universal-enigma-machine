#ifndef REFLECTORSELECT_H
#define REFLECTORSELECT_H

#include <wx/wx.h>
#include <enigma/Reflector.h>
#include <vector>

class ReflectorSelect : public wxComboBox
{
    public:
        ReflectorSelect(wxWindow* parent, const wxPoint &pos, const wxSize &size);
        ~ReflectorSelect();
        void loadReflectors(std::vector<std::string> reflectors);

    private:
        void OnChoose(wxCommandEvent& event);
};
enum
{
    ID_REFLECTOR_SELECTOR = 400
};
#endif