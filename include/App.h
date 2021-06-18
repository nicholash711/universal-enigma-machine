#ifndef APP_H
#define APP_H

#include <wx/wx.h>
#include <appcomponents/MainFrame.h>

class App : public wxApp
{
    private:
        MainFrame* mMainFrame = nullptr;
        
    public:
        App();
        ~App();
        virtual bool OnInit();
};

#endif