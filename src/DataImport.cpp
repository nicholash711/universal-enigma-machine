#include <DataImport.h>
#include <appcomponents/MainFrame.h>
#include <iostream>

namespace json = rapidjson;

DataImport::DataImport(wxWindow* parent, std::string file="")
{
    this->parent = parent;

    char loc[] = "data/";
    std::strcat(loc, file.c_str());
    FILE* f = fopen(loc, "rb");
    char readBuffer[4096];
    json::FileReadStream in(f, readBuffer, sizeof(readBuffer));
    doc.ParseStream(in);
    const json::Value& models = doc["models"];
    for(auto& model : models.GetArray())
    {
        objects[std::string(model["name"].GetString())] = &model;
    }

}

std::vector<std::string> DataImport::getModelList()
{
    std::vector<std::string> names;
    for(auto& model : objects)
        names.push_back(model.first);

    return names;
}

const json::Value* DataImport::getModel(std::string name)
{
    return objects[name];
}

std::vector<std::string> DataImport::getRotorList(std::string model)
{
    std::vector<std::string> rotors;
    for(auto& m : objects[model]->operator[]("rotors").GetArray())
        rotors.push_back(m["rotor"].GetString());
        
    return rotors;
}

std::vector<std::string> DataImport::getRotor4(std::string model)
{
    std::vector<std::string> rotors;
    for(auto& m : objects[model]->operator[]("rotor 4").GetArray())
        rotors.push_back(m["rotor"].GetString());
        
    return rotors;
}

std::vector<std::string> DataImport::getReflectorList(std::string model)
{
    std::vector<std::string> reflectors;
    for(auto& m : objects[model]->operator[]("reflectors").GetArray())
        reflectors.push_back(m["reflector"].GetString());
    return reflectors;
}

std::array<std::string, 3> DataImport::loadRotor(std::string name)
{
    std::string model = wxDynamicCast(parent, MainFrame)->getModel();
    const json::Value& rotors = objects[model]->operator[]("rotors");
    std::array<std::string, 3> rotor;
    for(auto& m : rotors.GetArray())
        if(m["rotor"].GetString() == name)
        {
            rotor = {std::string(m["wiring"].GetString()), std::string(m["turnover"].GetString()), std::string(m["rotor"].GetString())};
            break;
        }
    return rotor;
}

std::array<std::string, 2> DataImport::loadRotorFour(std::string name)
{
    std::string model = wxDynamicCast(parent, MainFrame)->getModel();
    const json::Value& rotors = objects[model]->operator[]("rotor 4");
    std::array<std::string, 2> rotor;
    for(auto& m : rotors.GetArray())
        if(m["rotor"].GetString() == name)
        {
            rotor = {std::string(m["wiring"].GetString()), std::string(m["rotor"].GetString())};
            break;
        }
    return rotor;
}

std::array<std::string, 2> DataImport::loadReflector(std::string name)
{
    std::string model = wxDynamicCast(parent, MainFrame)->getModel();
    const json::Value& reflectors = objects[model]->operator[]("reflectors");
    std::array<std::string, 2> reflector;
    for(auto& m : reflectors.GetArray())
    {
        if(m["reflector"].GetString() == name)
        {
            reflector = {std::string(m["wiring"].GetString()), std::string(m["reflector"].GetString())};
            break;
        }
    }
    return reflector;
}

std::string DataImport::loadEntryWheel(std::string model)
{
    return std::string(objects[model]->operator[]("entry wheel").GetString());
    
}

bool DataImport::hasFour(std::string model)
{
    return objects[model]->HasMember("rotor 4");
}

bool DataImport::hasPlugboard(std::string model)
{
    return objects[model]->operator[]("plugboard").GetBool();
}