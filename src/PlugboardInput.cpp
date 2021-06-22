#include <appcomponents/PlugboardInput.h>

PlugboardInput::PlugboardInput(wxWindow* parent, Plugboard* plug, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize)
    : wxTextCtrl(parent, ID_PLUGBOARD, "", pos, size, wxTE_PROCESS_ENTER)
{
    this->Bind(wxEVT_TEXT_ENTER, OnEnter, this);
    this->plugboard = plug;
}

PlugboardInput::~PlugboardInput()
{

}

void PlugboardInput::OnEnter(wxCommandEvent& event)
{

}
