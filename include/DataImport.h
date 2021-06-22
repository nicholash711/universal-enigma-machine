#ifndef DATAIMPORT_H
#define DATAIMPORT_H

#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <enigma/Reflector.h>
#include <enigma/Rotor.h>
#include <vector>
#include <map>

namespace json = rapidjson;

typedef json::GenericValue<json::UTF8<char>, json::MemoryPoolAllocator<json::CrtAllocator>> j_Value;

class DataImport
{
    private:
        json::Document doc;
        std::map<std::string, const json::Value*> objects;
        // json::GenericValue<json::UTF8<>, json::MemoryPoolAllocator<>>

    public:
        DataImport(std::string file);
        std::vector<std::string> getModelList();
        const j_Value* getModel(std::string name);
        std::vector<std::string> getRotorList(std::string model);
        std::vector<std::string> getRotor4(std::string name);
        std::vector<std::string> getReflectorList(std::string model);
        void loadRotor(std::string name, std::string rotor, Rotor* rot); 
        void loadFour(std::string name, std::string rotor, Rotor* rot);
        void loadReflector(std::string name, Reflector* ref);

        bool hasFour(std::string model);
        
};

#endif