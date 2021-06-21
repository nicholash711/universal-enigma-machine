#include <DataImport.h>
#include <cstdio>

using namespace rapidjson;

DataImport::DataImport(std::string file="")
{
    char loc[] = "data/";
    std::strcat(loc, file.c_str());
    printf("%s\n", loc);
    FILE* f = fopen(loc, "rb");
    char readBuffer[4096];
    FileReadStream in(f, readBuffer, sizeof(readBuffer));
    json.ParseStream(in);
}

std::vector<std::string> DataImport::getModels()
{
    std::vector<std::string> names;
    const Value& models = json["models"];

    printf("%d\n", models.IsArray());

    for(auto& model : models.GetArray())
    {
        names.push_back(model["name"].GetString());
        printf("%s\n", model["name"].GetString());
    }


    return names;
}