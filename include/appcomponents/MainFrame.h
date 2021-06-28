#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <enigma/Enigma.h>
#include <DataImport.h>
#include <appcomponents/RotorSelect.h>
#include <appcomponents/CharSpin.h>
#include <appcomponents/ReflectorSelect.h>
#include <appcomponents/PlugboardInput.h>

class MainFrame : public wxFrame
{ 
    public:
        MainFrame();
        ~MainFrame();
        std::string getModel();
        DataImport* getFile();
        Enigma* getEnigma();

        void loadComponents(std::string name);
        void OnPlugboardUpdate(std::string plugs, Plugboard& plugboard);
        void OnRotorSpin();
        void OnRingSpin();

    private:
        Enigma* enigma = nullptr;
        wxTextCtrl* input = nullptr;
        wxTextCtrl* output = nullptr;
        RotorSelect* rotors[4];
        CharSpin* rotSpin[4];
        CharSpin* ringSpin[4];
        ReflectorSelect* reflectors = nullptr;
        PlugboardInput* plugboardInput = nullptr;
        DataImport* file = nullptr;
        std::string model = "";

        void loadRotors(std::string name);

        void OnPress(wxCommandEvent& event);
        void PressFile(wxCommandEvent& event);
        void OnModelChoose(wxCommandEvent& event);
        void OnIdleEvent(wxIdleEvent& event);

        wxDECLARE_DYNAMIC_CLASS(MainFrame);
};

#endif