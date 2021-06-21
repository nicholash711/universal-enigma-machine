#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/statline.h>
#include <enigma/Enigma.h>

class MainFrame : public wxFrame
{ 
    public:
        MainFrame();
        ~MainFrame();
        void loadComponents();

    private:
        Enigma* enigma = nullptr;
        wxTextCtrl* input = nullptr;
        wxTextCtrl* output = nullptr;
        wxStaticText* text = nullptr;
        wxStaticLine* line = nullptr;

        void OnPress(wxCommandEvent& event);
        void PressFile(wxCommandEvent& event);
};

#endif