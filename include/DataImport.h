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
        void loadRotorFour(std::string model, std::string rotor, Rotor* rot);
        void loadReflector(std::string model, std::string reflector, Reflector* ref);
        void loadEntryWheel(std::string model, EntryWheel* wheel);

        bool hasFour(std::string model);
        bool hasPlugboard(std::string model);        
};

#endif