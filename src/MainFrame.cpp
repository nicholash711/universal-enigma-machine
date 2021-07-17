#include <appcomponents/MainFrame.h>
#include <appcomponents/ModelSelect.h>
#include <wx/statline.h>

wxIMPLEMENT_DYNAMIC_CLASS(MainFrame, wxWindow)

MainFrame::MainFrame() : 
    wxFrame(nullptr, wxID_ANY, "Enigma Machine", wxPoint(100, 100), wxSize(800, 600),  wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    this->SetBackgroundColour(wxColour(230, 230, 230));
    wxStaticText* text = nullptr;
    wxStaticLine* line = nullptr;

    enigma = new Enigma();


    // Menu Initialization
    wxMenuBar* menuBar = new wxMenuBar();
    wxMenu* menuFile = new wxMenu();
    menuFile->Append(10, "Settings", "Show Enigma Settings");
    menuFile->Append(20, "Reflector", "Show Reflector");
    menuFile->Append(30, "Entry Wheel", "Show EKW wiring");
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, PressFile, this, 10);
    Bind(wxEVT_MENU, PressPlug, this, 20);
    Bind(wxEVT_MENU, PressEKW, this, 30);


    // Model Menu Creation
    text = new wxStaticText(this, wxID_ANY, "Enigma Model: ", wxPoint(10, 12), wxSize(100, 20));
    ModelSelect* menu = new ModelSelect(this, wxPoint(110, 10), wxSize(300, 24));
    line = new wxStaticLine(this, wxID_ANY, wxPoint(10, 45), wxSize(780, 1));
    

    // Rotor Controls Creation
    for(int i = 0; i < 4; i++)
    {
        const std::string rotor = "Rotor " + std::to_string(i + 1) + ":";
        text = new wxStaticText(this, wxID_ANY, std::string("Rotor " + std::to_string(i + 1) + ":"), wxPoint(10, 62 + 40 * i), wxSize(50, 20));
        rotors[i] = new RotorSelect(this, i, wxPoint(60, 60 + 40 * i), wxSize(70, 20));
        text = new wxStaticText(this, wxID_ANY, "Rotor Position:", wxPoint(150, 62 + 40 * i), wxSize(80, 20));
        rotSpin[i] = new CharSpin(this, i, ROTOR_SPIN, wxPoint(240, 60 + 40 * i), wxSize(40, 20));
        text = new wxStaticText(this, wxID_ANY, "Ring Positon:", wxPoint(300, 62 + 40 * i), wxSize(80, 20));
        ringSpin[i] = new CharSpin(this, i, RING_SPIN, wxPoint(380, 60 + 40 * i), wxSize(40, 20));

    }


    // Entry Wheel, Reflector, & Plugboard Controls Creation
    text = new wxStaticText(this, wxID_ANY, "Reflector:", wxPoint(440, 62), wxSize(60, 20));
    reflectors = new ReflectorSelect(this, wxPoint(500, 60), wxSize(110, 20));
    text = new wxStaticText(this, wxID_ANY, "Rotor:", wxPoint(620, 62), wxSize(40, 20));
    ukwPos = new CharSpin(this, 5, ROTOR_SPIN, wxPoint(660, 60), wxSize(40, 20));
    text = new wxStaticText(this, wxID_ANY, "Ring:", wxPoint(710, 62), wxSize(40, 20));
    ukwRing = new CharSpin(this, 5, RING_SPIN, wxPoint(750, 60), wxSize(40, 20));

    text = new wxStaticText(this, wxID_ANY, "Plugboard Setting:", wxPoint(440, 102), wxSize(110, 20));
    plugboardInput = new PlugboardInput(this, wxPoint(550, 100), wxSize(240, 24));
    line = new wxStaticLine(this, wxID_ANY, wxPoint(10, 210), wxSize(780, 1));


    // Input / Output Textbox Creation
    text = new wxStaticText(this, wxID_ANY, "Input:", wxPoint(10, 222), wxSize(50, 18));
    text = new wxStaticText(this, wxID_ANY, "Output:", wxPoint(410, 222), wxSize(50, 18));
    input = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 240), wxSize(380, 270), wxTE_MULTILINE);
    output = new wxTextCtrl(this, wxID_ANY, "", wxPoint(410, 240), wxSize(380, 270), wxTE_MULTILINE | wxTE_READONLY);

    input->Bind(wxEVT_TEXT, OnInput, this);

    //File Input
    file = new DataImport(this, "models.json");
    menu->loadModels(file->getModelList());
    menu->Bind(wxEVT_COMBOBOX, OnModelChoose, this);

}

MainFrame::~MainFrame()
{
}

std::string MainFrame::getModel()
{
    return model;
}

DataImport* MainFrame::getFile()
{
    return file;
}

Enigma* MainFrame::getEnigma()
{
    return enigma;
}

void MainFrame::loadComponents(std::string name)
{
    model = name;
    loadRotors(model);
    reflectors->loadReflectors(file->getReflectorList(model));
    enigma->setEntryWheel(file->loadEntryWheel(model));
    plugboardInput->ChangeValue("");
    enigma->getPlugboard()->clear();
    plugboardInput->Enable(file->hasPlugboard(model));
    enigma->doesDouble(file->doesDouble(model));
    ReflectorUpdate();
}

void MainFrame::ReflectorUpdate()
{
    ukwPos->setText('A');
    ukwRing->setText('A');
    ukwPos->enable(file->UKWRotate(model));
    ukwRing->enable(file->UKWRotate(model));
}

void MainFrame::updateRotor(int i)
{
    getEnigma()->setPosition(rotSpin[i + 1]->getText(), i);
    getEnigma()->setRing(ringSpin[i + 1]->getText(), i);
}

void MainFrame::update()
{
    output->SetValue(enigma->encrypt(std::string(input->GetValue())));
}

void MainFrame::loadRotors(std::string name)
{
    for(int i = 0; i < 4; i++)
    {
        rotors[i]->Clear();
        rotSpin[i]->setText('A');
        ringSpin[i]->setText('A');
    }
    if(file->hasFour(name))
    {
        enigma->hasFourRotors(true);
        rotors[3]->Enable(true);
        rotSpin[3]->enable(true);
        ringSpin[3]->enable(true);
        for(int i = 1; i < 4; i++)
            rotors[i]->loadChoices(file->getRotorList(name));
        rotors[0]->loadChoices(file->getRotor4(name));
    }
    else
    {
        enigma->hasFourRotors(false);
        for(int i = 0; i < 3; i++)
            rotors[i]->loadChoices(file->getRotorList(name));
        rotors[3]->Enable(false);
        rotSpin[3]->enable(false);
        ringSpin[3]->enable(false);
    }
}

void MainFrame::OnInput(wxCommandEvent& event)
{
    update();
}

void MainFrame::PressFile(wxCommandEvent& event)
{
    std::cout << "Model: " << model << std::endl;
    std::cout << *enigma << std::endl;  
}

void MainFrame::PressPlug(wxCommandEvent& event)
{
    std::cout << *(enigma->getReflector()) << std::endl;
}

void MainFrame::PressEKW(wxCommandEvent& event)
{
    std::cout << *(enigma->getEntryWheel()) << std::endl;
}
void MainFrame::OnModelChoose(wxCommandEvent& event)
{
    ModelSelect* menu = (ModelSelect*)event.GetEventObject();
    if(model != std::string(menu->GetValue()))
        loadComponents(std::string(menu->GetValue()));
}