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
        int rotor = -1;
        int type = 0;

    public:
        CharSpin(wxWindow* parent, int n, int t, const wxPoint &pos, const wxSize &size);
        ~CharSpin();
        void setText(char c);
        char getText();
        void enable(bool enabled);

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
    ID_ARROWS = 350,
    RING_SPIN = 301,
    ROTOR_SPIN = 302
};

#endif