#include <DataImport.h>
#include <cstdio>

using namespace rapidjson;

DataImport::DataImport(std::string file="")
{
    char loc[] = "data/";
    std::strcat(loc, file.c_str());
    FILE* f = fopen(loc, "rb");
    char readBuffer[4096];
    FileReadStream in(f, readBuffer, sizeof(readBuffer));
    json.ParseStream(in);
}

std::vector<std::string> DataImport::getModels()
{
    std::vector<std::string> names;
    const Value& models = json["models"];
    for(auto& model : models.GetArray())
    {
        names.push_back(model["name"].GetString());
    }


    return names;
}