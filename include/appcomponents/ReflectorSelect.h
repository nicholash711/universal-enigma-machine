#ifndef REFLECTORSELECT_H
#define REFLECTORSELECT_H

#include <wx/wx.h>
#include <enigma/Reflector.h>
#include <vector>

class ReflectorSelect : public wxComboBox
{
    public:
        ReflectorSelect(wxWindow* parent, const wxPoint &pos, const wxSize &size, Reflector* ref);
        ~ReflectorSelect();
        void loadReflectors(std::vector<std::string> reflectors);

    private:
        Reflector* reflector;
        void OnChoose(wxCommandEvent& event);
};
enum
{
    ID_REFLECTOR_SELECTOR = 400
};
#endif