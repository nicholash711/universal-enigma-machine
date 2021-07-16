#include <iostream>
#include <algorithm>
#include <enigma/Reflector.h>

Reflector::Reflector()
{
    name = "";
    reflector.fill("");
    ring = 0;
}

Reflector::Reflector(Reflector& ref)
{
    this->name = ref.name;
    this->reflector = ref.reflector;
    this->ring = 'A';
}

Reflector::Reflector(std::string wiring, std::string name)
{
    this->name = name;
    for(int i = 0; i < 26; i++)
        reflector[i] = std::string() + (char)(i + 65) + wiring[i];
}

std::string Reflector::getName()
{
    return name;
}

int Reflector::reflect(char c)
{
    c = toupper(c);
    char encrypted = reflector[c - 65][1];
    return (encrypted - reflector[0][0] + 26) % 26;
}

int Reflector::reflect(int c)
{
    char encrypted = reflector[c][1];
    return (encrypted - reflector[0][0] + 26) % 26;
}

bool Reflector::isRotatable()
{
    return rotatable;
}

char Reflector::getCurrent()
{
    return reflector[0][0];
}

char Reflector::getRing()
{
    return ring;
}

void Reflector::setRotatable(bool rotate)
{
    rotatable = rotate;
}

void Reflector::setReflectorPosition(char c)
{
    char current = reflector[0][0];
    int shift = (c - current + 26) % 26;
    std::rotate(reflector.begin(), reflector.begin() + shift, reflector.end());
}

void Reflector::setRingPosition(char c)
{
    int shift = (c - ring + 26) % 26;
    std::array<std::string, 26> temp = reflector;
    for(int i = 0; i < 26; i++)
        reflector[i] = std::string() + temp[i][0] + (char)((temp[(i - shift + 26) % 26][1] + shift - 65) % 26 + 65);
    this->ring = c;
}

void Reflector::rotate()
{
    std::rotate(reflector.begin(), reflector.begin() + 1, reflector.end());
}


void Reflector::operator=(Reflector &reflector)
{
    name = reflector.name;
    Reflector::reflector = reflector.reflector;
}

std::ostream& operator<<(std::ostream &out, Reflector &reflector)
{
    out << "Reflector " << reflector.name << "\n";
    out << "Reflector Positon: " << reflector.reflector[0][0] << std::endl;
    out << "Ring Setting: " << reflector.ring << std::endl;
    for(int i = 0; i < 26; i++)
        out << (char)(i + 65) << " - " << reflector.reflector[i][1] << "\n";
    return out;
}