#include <iostream>
#include <enigma/Reflector.h>

Reflector::Reflector()
{
    name = "";
    reflector.fill(0);
}
Reflector::Reflector(std::string wiring, std::string n)
{
    name = n;
    for(int i = 0; i < 26; i++)
        reflector[i] = wiring[i];
}

std::string Reflector::getName()
{
    return name;
}

int Reflector::reflect(char c)
{
    return reflector[c - 65] - 65;
}

int Reflector::reflect(int c)
{
    return reflector[c] - 65;
}
void Reflector::operator=(Reflector &reflector)
{
    name = reflector.name;
    Reflector::reflector = reflector.reflector;
}

std::ostream& operator<<(std::ostream &out, Reflector &reflector)
{
    out << "Reflector " << reflector.name << "\n";
    for(int i = 0; i < 26; i++)
        out << (char)(i + 65) << " - " << reflector.reflector[i] << "\n";
    return out;
}