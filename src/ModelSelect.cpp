#include <appcomponents/ModelSelect.h>


ModelSelect::ModelSelect(wxWindow* parent, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize) :
    wxComboBox(parent, ID_MODEL_SELECTOR, "", pos, size)
{
    this->Bind(wxEVT_COMBOBOX, OnChoose, this);
}

ModelSelect::~ModelSelect()
{
}

void ModelSelect::OnChoose(wxCommandEvent& event)
{
    wxString choice = this->GetValue();
}

void ModelSelect::loadModels()
{

}