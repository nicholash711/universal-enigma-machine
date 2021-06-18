#ifndef CHARSPIN_H
#define CHARSPIN_H

#include <wx/wx.h>
#include <wx/spinbutt.h>

class CharSpin : public wxSpinButton
{
    private:
        wxTextCtrl* textbox = nullptr;
        char text = 0;
        bool gotFocus = false;

    public:
        CharSpin(wxWindow* parent, const wxPoint &pos, const wxSize &size);
        ~CharSpin();
        void setText(char c);

    private:
        void OnTextChange(wxCommandEvent &event);
        void OnTextEnter(wxCommandEvent &event);
        void OnLeftClick(wxMouseEvent &event);
        void OnIdle(wxIdleEvent &event);
        void OnLoseFocus(wxFocusEvent &event);
        bool isNum(std::string str);
        void popup();

        void OnSpinUp(wxSpinEvent &event);
        void OnSpinDown(wxSpinEvent &event);

};
enum
{
    ID_TEXT_BOX = 300,
    ID_ARROWS = 350 
};

#endif