#ifndef DATAIMPORT_H
#define DATAIMPORT_H

#include <wx/wx.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <enigma/Reflector.h>
#include <enigma/Rotor.h>
#include <enigma/EntryWheel.h>
#include <vector>
#include <map>

namespace json = rapidjson;

typedef json::GenericValue<json::UTF8<char>, json::MemoryPoolAllocator<json::CrtAllocator>> j_Value;

class DataImport
{
    private:
        wxWindow* parent;
        json::Document doc;
        std::map<std::string, const json::Value*> objects;
        // json::GenericValue<json::UTF8<>, json::MemoryPoolAllocator<>>

    public:
        DataImport(wxWindow* parent ,std::string file);
        std::vector<std::string> getModelList();
        const json::Value* getModel(std::string name);
        std::vector<std::string> getRotorList(std::string model);
        std::vector<std::string> getRotor4(std::string name);
        std::vector<std::string> getReflectorList(std::string model);
        std::array<std::string, 3> loadRotor(std::string rotor); 
        std::array<std::string, 2> loadRotorFour(std::string rotor);
        std::array<std::string, 2> loadReflector(std::string reflector);
        std::string loadEntryWheel(std::string model);

        bool hasFour(std::string model);
        bool hasPlugboard(std::string model);     
        bool doesDouble(std::string model);
        bool UKWRotate(std::string model);  
};

#endif