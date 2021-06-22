#ifndef PLUGBOARDINPUT_H
#define PLUGBOARDINPUT_H

#include <wx/wx.h>
#include <enigma/Plugboard.h>

class PlugboardInput : public wxTextCtrl
{
    public:
        PlugboardInput(wxWindow* parent, Plugboard* plug, const wxPoint &pos, const wxSize &size);
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