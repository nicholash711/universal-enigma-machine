#include <App.h>

wxIMPLEMENT_APP(App);

App::App()
{
}

App::~App()
{
}

bool App::OnInit()
{
    mMainFrame = new MainFrame();
    mMainFrame->Show();
    return true;
}