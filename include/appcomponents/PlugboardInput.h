#ifndef PLUGBOARDINPUT_H
#define PLUGBOARDINPUT_H

#include <wx/wx.h>

class PlugboardInput : public wxTextCtrl
{
    public:
        PlugboardInput(wxWindow* parent, const wxPoint &pos, const wxSize &size);
        ~PlugboardInput();

    private:
        void OnChange(wxCommandEvent& event);
        void OnEnter(wxCommandEvent& event);
};
enum
{
    ID_PLUGBOARD = 500
};
#endif