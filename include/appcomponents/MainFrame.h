#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/statline.h>
#include <enigma/Enigma.h>
#include <DataImport.h>
#include <appcomponents/RotorSelect.h>
#include <appcomponents/CharSpin.h>

class MainFrame : public wxFrame
{ 
    public:
        MainFrame();
        ~MainFrame();
        void loadComponents(std::string name);

    private:
        Enigma* enigma = nullptr;
        DataImport* file = nullptr;
        wxTextCtrl* input = nullptr;
        wxTextCtrl* output = nullptr;
        wxStaticText* text = nullptr;
        wxStaticLine* line = nullptr;
        std::string model = "";
        RotorSelect* rotors[4];
        CharSpin* spin1[4];
        CharSpin* spin2[4];

        void loadRotors(std::string name);

        void OnPress(wxCommandEvent& event);
        void PressFile(wxCommandEvent& event);
        void OnModelChoose(wxCommandEvent& event);
};

#endif