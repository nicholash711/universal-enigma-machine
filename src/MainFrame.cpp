#include <rapidjson/document.h>
#include <appcomponents/MainFrame.h>
#include <appcomponents/ModelSelect.h>
#include <appcomponents/CharSpin.h>
#include <appcomponents/RotorSelect.h>
#include <appcomponents/PlugboardInput.h>
#include <appcomponents/ReflectorSelect.h>
#include <cstdio>

namespace json = rapidjson;

MainFrame::MainFrame() : 
    wxFrame(nullptr, wxID_ANY, "Enigma Machine", wxPoint(100, 100), wxSize(800, 600),  wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    this->SetBackgroundColour(wxColour(230, 230, 230));

    // Menu Initialization
    wxMenuBar* menuBar = new wxMenuBar();
    wxMenu* menuFile = new wxMenu();
    menuFile->Append(10, "File... \tCtrl+H", "Click Me!");
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, PressFile, this, 10);


    // Model Menu Creation
    text = new wxStaticText(this, wxID_ANY, "Enigma Model: ", wxPoint(10, 12), wxSize(100, 20));
    ModelSelect* menu = new ModelSelect(this, wxPoint(110, 10), wxSize(300, 24));
    line = new wxStaticLine(this, wxID_ANY, wxPoint(10, 45), wxSize(780, 1));

    menu->Bind(wxEVT_COMBOBOX, OnModelChoose, this);
    

    // Rotor Controls Creation
    for(int i = 0; i < 4; i++)
    {
        const std::string rotor = "Rotor " + std::to_string(i + 1) + ":";
        text = new wxStaticText(this, wxID_ANY, std::string("Rotor " + std::to_string(i + 1) + ":"), wxPoint(10, 62 + 40 * i), wxSize(50, 20));
        rotors[i] = new RotorSelect(this, wxPoint(60, 60 + 40 * i), wxSize(40, 20));
        text = new wxStaticText(this, wxID_ANY, "Rotor Position:", wxPoint(120, 62 + 40 * i), wxSize(80, 20));
        spin1[i] = new CharSpin(this, wxPoint(210, 60 + 40 * i), wxSize(40, 20));
        text = new wxStaticText(this, wxID_ANY, "Ring Positon:", wxPoint(270, 62 + 40 * i), wxSize(80, 20));
        spin2[i] = new CharSpin(this, wxPoint(350, 60 + 40 * i), wxSize(40, 20));

    }


    // Reflector & Plugboard Controls Creation
    text = new wxStaticText(this, wxID_ANY, "Reflector:", wxPoint(410, 62), wxSize(60, 20));
    ReflectorSelect* reflectorSelect = new ReflectorSelect(this, wxPoint(470, 60), wxSize(320, 20));
    text = new wxStaticText(this, wxID_ANY, "Plugboard Setting:", wxPoint(410, 102), wxSize(110, 20));
    PlugboardInput* plugboardInput = new PlugboardInput(this, wxPoint(520, 100), wxSize(270, 24));
    line = new wxStaticLine(this, wxID_ANY, wxPoint(10, 210), wxSize(780, 1));


    // Input / Output Textbox Creation
    text = new wxStaticText(this, wxID_ANY, "Input:", wxPoint(10, 222), wxSize(50, 18));
    text = new wxStaticText(this, wxID_ANY, "Output:", wxPoint(410, 222), wxSize(50, 18));
    input = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 240), wxSize(380, 270), wxTE_MULTILINE);
    output = new wxTextCtrl(this, wxID_ANY, "", wxPoint(410, 240), wxSize(380, 270), wxTE_MULTILINE | wxTE_READONLY);
    wxButton* encode = new wxButton(this, wxID_ANY, "Encode", wxPoint(360, 520), wxSize(80, 20));

    encode->Bind(wxEVT_BUTTON, OnPress, this);

    enigma = new Enigma();
    file = new DataImport("models.json");
    menu->loadModels(file->getModelList());
}

MainFrame::~MainFrame()
{
}

void MainFrame::loadComponents(std::string name)
{
    model = name;
    loadRotors(name);
}

void MainFrame::loadRotors(std::string name)
{
    for(int i = 0; i < 4; i++)
    {
        rotors[i]->Clear();
        spin1[i]->setText('A');
        spin2[i]->setText('A');
    }
    if(file->hasFour(name))
    {
        rotors[3]->Enable(true);
        spin1[3]->enable(true);
        spin2[3]->enable(true);
        for(int i = 1; i < 4; i++)
            rotors[i]->loadChoices(file->getRotorList(name));
        rotors[0]->loadChoices(file->getRotor4(name));
    }
    else
    {
        for(int i = 0; i < 3; i++)
            rotors[i]->loadChoices(file->getRotorList(name));
        rotors[3]->Enable(false);
        spin1[3]->enable(false);
        spin2[3]->enable(false);
        
    }
        

}

void MainFrame::OnPress(wxCommandEvent& event)
{
    output->SetValue(enigma->encrypt(std::string(input->GetValue())));
}

void MainFrame::PressFile(wxCommandEvent& event)
{
    std::cout << "File Pressed" << std::endl;  
}

void MainFrame::OnModelChoose(wxCommandEvent& event)
{
    ModelSelect* menu = (ModelSelect*)event.GetEventObject();
    if(model != std::string(menu->GetValue()))
        loadComponents(std::string(menu->GetValue()));
}