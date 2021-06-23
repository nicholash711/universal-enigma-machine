#include <DataImport.h>

namespace json = rapidjson;

DataImport::DataImport(std::string file="")
{
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

void DataImport::loadRotor(std::string model, std::string rotor, Rotor* r)
{
    const json::Value& rotors = objects[model]->operator[]("rotors");
    for(auto& m : rotors.GetArray())
    {
        if(m["rotor"].GetString() == rotor)
        {
            r = new Rotor(std::string(m["wiring"].GetString()), std::string(m["turnover"].GetString()), std::string(m["rotor"].GetString()));
            break;
        }
    }
}

void DataImport::loadRotorFour(std::string model, std::string rotor, Rotor* r)
{
    const json::Value& rotors = objects[model]->operator[]("rotor 4");
    for(auto& m : rotors.GetArray())
    {
        if(m["rotor"].GetString() == rotor)
        {
            r = new Rotor(std::string(m["wiring"].GetString()), "", std::string(m["rotor"].GetString()));
            break;
        }
    }
}

void DataImport::loadReflector(std::string model, std::string reflector, Reflector* ref)
{
    const json::Value& reflectors = objects[model]->operator[]("reflectors");
    for(auto& m : reflectors.GetArray())
    {
        if(m["reflector"].GetString() == reflector)
        {
            ref = new Reflector(std::string(m["wiring"].GetString()), std::string(m["reflector"].GetString()));
            break;
        }
    }
}

void DataImport::loadEntryWheel(std::string model, EntryWheel* wheel)
{
    wheel = new EntryWheel(std::string(objects[model]->operator[]("entry wheel").GetString()));
    
}

bool DataImport::hasFour(std::string model)
{
    return objects[model]->HasMember("rotor 4");
}

bool DataImport::hasPlugboard(std::string model)
{
    return objects[model]->operator[]("plugboard").GetBool();
}