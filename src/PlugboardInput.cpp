#include <appcomponents/PlugboardInput.h>
#include <appcomponents/MainFrame.h>
#include <enigma/Enigma.h>

PlugboardInput::PlugboardInput(wxWindow* parent, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize)
    : wxTextCtrl(parent, ID_PLUGBOARD, "", pos, size, wxTE_PROCESS_ENTER)
{
    this->Bind(wxEVT_TEXT, OnChange, this);
    this->Bind(wxEVT_TEXT_ENTER, OnEnter, this);
}

PlugboardInput::~PlugboardInput()
{

}

void PlugboardInput::OnChange(wxCommandEvent& event)
{
    MainFrame* frame = wxDynamicCast(GetParent(), MainFrame);
    if(std::string(GetValue()).size() != 0)
    {
        std::vector<std::string> plugs;
        std::string temp(GetValue());
        std::transform(temp.begin(), temp.end(), temp.begin(), toupper);
        ChangeValue(temp);
        SetInsertionPoint(GetLastPosition());
        char* buffer = new char[1024];
        strcpy(buffer, temp.c_str());
        char *token = strtok(buffer, " ");
        while(token != NULL)
        {
            plugs.push_back(token);
            token = strtok(NULL, " ");
        }
            
        if(frame->getEnigma()->setPlugs(plugs))
        {
            SetBackgroundColour(wxColour(*wxWHITE));
        }
        else
            SetBackgroundColour(wxColour(*wxRED));
    }
    else
        SetBackgroundColour(wxColour(*wxWHITE));

    frame->update();
    Refresh();
}

void PlugboardInput::OnEnter(wxCommandEvent& event)
{

}
