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
    menuFile->Append(10, "Settings... \tCtrl+H", "Show Enigma Settings");
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, PressFile, this, 10);


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
        rotSpin[i] = new CharSpin(this, i, wxPoint(240, 60 + 40 * i), wxSize(40, 20));
        text = new wxStaticText(this, wxID_ANY, "Ring Positon:", wxPoint(300, 62 + 40 * i), wxSize(80, 20));
        ringSpin[i] = new CharSpin(this, i, wxPoint(380, 60 + 40 * i), wxSize(40, 20));

    }


    // Entry Wheel, Reflector, & Plugboard Controls Creation
    text = new wxStaticText(this, wxID_ANY, "Reflector:", wxPoint(440, 62), wxSize(60, 20));
    reflectors = new ReflectorSelect(this, wxPoint(500, 60), wxSize(290, 20));
    text = new wxStaticText(this, wxID_ANY, "Plugboard Setting:", wxPoint(440, 102), wxSize(110, 20));
    plugboardInput = new PlugboardInput(this, enigma->getPlugboard(), wxPoint(550, 100), wxSize(240, 24));
    line = new wxStaticLine(this, wxID_ANY, wxPoint(10, 210), wxSize(780, 1));


    // Input / Output Textbox Creation
    text = new wxStaticText(this, wxID_ANY, "Input:", wxPoint(10, 222), wxSize(50, 18));
    text = new wxStaticText(this, wxID_ANY, "Output:", wxPoint(410, 222), wxSize(50, 18));
    input = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 240), wxSize(380, 270), wxTE_MULTILINE);
    output = new wxTextCtrl(this, wxID_ANY, "", wxPoint(410, 240), wxSize(380, 270), wxTE_MULTILINE | wxTE_READONLY);
    wxButton* encode = new wxButton(this, wxID_ANY, "Encode", wxPoint(360, 520), wxSize(80, 20));

    encode->Bind(wxEVT_BUTTON, OnPress, this);

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
    plugboardInput->Enable(file->hasPlugboard(model));
}

void MainFrame::OnPlugboardUpdate(std::string plugs, Plugboard& plugboard)
{

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
        rotors[3]->Enable(true);
        rotSpin[3]->enable(true);
        ringSpin[3]->enable(true);
        for(int i = 1; i < 4; i++)
            rotors[i]->loadChoices(file->getRotorList(name));
        rotors[0]->loadChoices(file->getRotor4(name));
    }
    else
    {
        for(int i = 0; i < 3; i++)
            rotors[i]->loadChoices(file->getRotorList(name));
        rotors[3]->Enable(false);
        rotSpin[3]->enable(false);
        ringSpin[3]->enable(false);
    }
}

void MainFrame::OnPress(wxCommandEvent& event)
{
    output->SetValue(enigma->encrypt(std::string(input->GetValue())));
}

void MainFrame::PressFile(wxCommandEvent& event)
{
    std::cout << "Model: " << model << std::endl;
    std::cout << enigma->print() << std::endl;  
}

void MainFrame::OnModelChoose(wxCommandEvent& event)
{
    ModelSelect* menu = (ModelSelect*)event.GetEventObject();
    if(model != std::string(menu->GetValue()))
        loadComponents(std::string(menu->GetValue()));
}

void MainFrame::OnIdleEvent(wxIdleEvent& event)
{
    if(file->hasFour(model))
        for(int i = 0; i < 4; i++)
        {
            if(rotSpin[i]->getText() != enigma->getRotors()[i]->getCurrent())
                enigma->setPosition(rotSpin[i]->getText(), i);
            if(ringSpin[i]->getText() != enigma->getRotors()[i]->getRing())
                enigma->setRing(ringSpin[i]->getText(), i);
        }
    else
        for(int i = 0; i < 3; i++)
        {
            if(rotSpin[i]->getText() != enigma->getRotors()[i]->getCurrent())
                enigma->setPosition(rotSpin[i]->getText(), i);
            if(ringSpin[i]->getText() != enigma->getRotors()[i]->getRing())
                enigma->setRing(ringSpin[i]->getText(), i);
        }
}