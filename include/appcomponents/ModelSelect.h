#ifndef MODELSELECT_H
#define MODELSELECT_H

#include <wx/wx.h>
#include <wx/combobox.h>

class ModelSelect : public wxComboBox
{
    
        
    public:
        ModelSelect(wxWindow* parent, const wxPoint &pos, const wxSize &size);
        ~ModelSelect();
        void loadModels(std::vector<wxString> models);

    private:
        void OnChoose(wxCommandEvent& event);
};
enum
{
    ID_MODEL_SELECTOR = 100
};

#endif
