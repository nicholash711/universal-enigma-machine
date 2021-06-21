#include <appcomponents/ModelSelect.h>


ModelSelect::ModelSelect(wxWindow* parent, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize) :
    wxComboBox(parent, ID_MODEL_SELECTOR, "", pos, size, {}, wxCB_READONLY)
{
}

ModelSelect::~ModelSelect()
{
}

void ModelSelect::OnChoose(wxCommandEvent& event)
{
}

void ModelSelect::loadModels(std::vector<std::string> models)
{
    std::vector<wxString> names;
    names.resize(models.size());
    std::transform(models.begin(), models.end(), names.begin(), [](std::string str){
        wxString name(str);
        return name;
    });
    this->Set(names);
}