#ifndef PLUGBOARDINPUT_H
#define PLUGBOARDINPUT_H

#include <wx/wx.h>
#include <enigma/Plugboard.h>

class PlugboardInput : public wxTextCtrl
{
    public:
        PlugboardInput(wxWindow* parent, const wxPoint &pos, const wxSize &size, Plugboard* plug);
        ~PlugboardInput();

    private:
        Plugboard* plugboard;
        void OnEnter(wxCommandEvent& event);
};
enum
{
    ID_PLUGBOARD = 500
};
#endif