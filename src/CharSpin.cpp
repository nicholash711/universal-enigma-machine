#include <appcomponents/CharSpin.h>
#include <appcomponents/MainFrame.h>
#include <enigma/Enigma.h>

CharSpin::CharSpin(wxWindow* parent, int n, int t, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize) :
    wxSpinButton(parent, ID_ARROWS, wxPoint(pos.x + size.x - 15, pos.y), wxSize(15, size.y), wxSP_WRAP)
{
    textbox = new wxTextCtrl(parent, ID_TEXT_BOX, "", pos, wxSize(size.x - 15, size.y), wxTE_PROCESS_ENTER);
    textbox->SetMaxLength(1);
    textbox->ChangeValue("A");
    text = textbox->GetValue()[0];

    this->Bind(wxEVT_SPIN_UP, OnSpinUp, this);
    this->Bind(wxEVT_SPIN_DOWN, OnSpinDown, this);

    textbox->Bind(wxEVT_TEXT, OnTextChange, this);
    textbox->Bind(wxEVT_TEXT_ENTER, OnTextEnter, this);
    textbox->Bind(wxEVT_LEFT_DOWN, OnLeftClick, this);
    textbox->Bind(wxEVT_IDLE, OnIdle, this);
    textbox->Bind(wxEVT_KILL_FOCUS, OnLoseFocus, this);

    rotor = n;
    type = t;
}

CharSpin::~CharSpin()
{
}

void CharSpin::setText(char c)
{
    textbox->ChangeValue((char)toupper(c));
    text = (char)toupper(c);

    MainFrame* frame = wxDynamicCast(GetParent(), MainFrame);
    if(type == ROTOR_SPIN)
    {
        frame->getEnigma()->setPosition(text, rotor);
    }
    else if(type == RING_SPIN)
    {
        frame->getEnigma()->setRing(text, rotor);
    }    
}

char CharSpin::getText()
{
    return text;
}

void CharSpin::enable(bool enabled)
{
    this->Enable(enabled);
    textbox->Enable(enabled);
}
////////////////////////////////////////////////////////
//    Spin Button Events
////////////////////////////////////////////////////////
void CharSpin::OnSpinUp(wxSpinEvent &event)
{
    this->setText((char)(((char)(textbox->GetValue()[0]) - 64) % 26 + 65));
}

void CharSpin::OnSpinDown(wxSpinEvent &event)   
{
    this->setText((char)(((char)(textbox->GetValue()[0]) - 40) % 26 + 65));
}

////////////////////////////////////////////////////////
//    Text Box Events
////////////////////////////////////////////////////////
void CharSpin::OnTextChange(wxCommandEvent &event)
{
    std::string str = std::string(textbox->GetValue());
    if(isNum(str))
    {
        textbox->SetMaxLength(2);
    }
    else if(str.length() > 1)
    {
        popup();
        std::cout << text << std::endl;
        textbox->ChangeValue(text);
    }
    else if(isalpha(str[0]) && text != str[0])
    {   
        setText(str[0]);
    }
    else
    {   
        popup();
        std::cout << text << std::endl;
        textbox->ChangeValue(text);
    }

}

void CharSpin::OnTextEnter(wxCommandEvent& event)
{
    std::string str = std::string(textbox->GetValue());
    if(str.empty())
        setText('A');
    else if(isNum(str))
    {
        int i = std::stoi(str);
        if(i >= 0 && i <= 26)
            setText(i + 64);
        else
        {
            popup();
            std::cout << text << std::endl;
            textbox->ChangeValue(text);
        }
        textbox->SetMaxLength(1);
    }
}

void CharSpin::OnLeftClick(wxMouseEvent& event)
{
    gotFocus = true;
    event.Skip();
}

void CharSpin::OnIdle(wxIdleEvent& event)
{
    if(gotFocus)
    {
        textbox->SelectAll();
        gotFocus = false;
    }
    event.Skip();
}

void CharSpin::OnLoseFocus(wxFocusEvent& event)
{   
    if(std::string(textbox->GetValue()).empty())
        setText('A');
    else if(isNum(std::string(textbox->GetValue())))
    {
        int i = std::stoi(std::string(textbox->GetValue()));
        if(i >= 0 && i <= 26)
            setText(i + 64);
        else
        {
            popup();
            std::cout << text << std::endl;
            textbox->ChangeValue(text);
        }
        textbox->SetMaxLength(1);
    }
    event.Skip();
}

bool CharSpin::isNum(std::string str)
{
    for(char c : str)
        if(!isdigit(c))
            return false;
    return true;
}

void CharSpin::popup()
{
    wxMessageDialog* popup = new wxMessageDialog(this, "Please type a single character or a number between 1 & 26.", "Error");
    popup->ShowModal();
}