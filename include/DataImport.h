#ifndef DATAIMPORT_H
#define DATAIMPORT_H

#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <vector>

class DataImport
{
    private:
        rapidjson::Document json;

    public:
        DataImport(std::string file);
        std::vector<std::string> getModels();

        
};

#endif