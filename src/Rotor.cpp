#include <iostream>
#include <cmath>
#include <algorithm>
#include <enigma/Rotor.h>

Rotor::Rotor()
{
    name = "";
    turnover = "";
    ring = 0;
    wiring.fill("");
}

Rotor::Rotor(Rotor& rotor)
{
    this->name = rotor.getName();
    this->turnover = rotor.getTurnover();
    this->ring = rotor.getRing();
    this->wiring = rotor.getWiring();
}

Rotor::Rotor(std::string wiring, std::string turnover, std::string name)
{
    this->name = name;
    this->turnover = turnover;
    for(char& c : this->turnover)
        c = toupper(c);
    ring = 'A';
    for(int i = 0; i < 26; i++)
        this->wiring[i] = std::string() + (char)(i + 65) + (char)toupper(wiring[i]);
}

std::string Rotor::getName()
{
    return name;
}

std::string Rotor::getTurnover()
{
    return turnover;
}

std::array<std::string, 26> Rotor::getWiring()
{
    return wiring;
}

char Rotor::getCurrent()
{
    return wiring[0][0];
}

char Rotor::getRing()
{   
    return ring;
}

int Rotor::encrypt(char c)
{
    c = toupper(c);
    char encrypted = wiring[c - 65][1];
    return (encrypted - wiring[0][0] + 26) % 26;
}

int Rotor::encrypt(int c)
{
    char encrypted = wiring[c][1];
    return (encrypted - wiring[0][0] + 26) % 26;
}

int Rotor::reencrypt(char c)
{
    c = toupper(c);
    char encrypt = wiring[c - 65][0];
    for(int i = 0; i < 26; i++)
    {
        if(wiring[i][1] == encrypt)
        {
            return i;
        }
    }
    return -1;
}

int Rotor::reencrypt(int c)
{
    char encrypt = wiring[c][0];
    for(int i = 0; i < 26; i++)
    {
        if(wiring[i][1] == encrypt)
        {
            return i;
        }
            
    }
    return -1;
}

/**
 * Rotates rotor by one to the left.
 * 
 * @returns boolean if rotation passes turnover value.
 */
bool Rotor::rotate()
{
    std::rotate(wiring.begin(), wiring.begin() + 1, wiring.end());
    return turnover.find(wiring[25][0]) != std::string::npos;
}

bool Rotor::setRotorPosition(char pos)
{
    char current = wiring[0][0];
    int shift = (pos - current + 26) % 26;
    std::rotate(wiring.begin(), wiring.begin() + shift, wiring.end());
    return true;
}

bool Rotor::setRingSetting(char pos)
{
    int shift = (pos - ring + 26) % 26;
    std::array<std::string, 26> temp = wiring;
    for(int i = 0; i < 26; i++)
        wiring[i] = std::string() + temp[i][0] + (char)((temp[(i - shift + 26) % 26][1] + shift - 65) % 26 + 65);
    this->ring = pos;
    return true;

}

void Rotor::reset()
{
    setRingSetting('A');
    setRotorPosition('A');
}

bool Rotor::operator==(Rotor &rotor)
{
    std::array<std::string, 26> temp = rotor.wiring;
    int shift = ('A' - rotor.getCurrent() + 26) % 26;
    std::rotate(temp.begin(), temp.begin() + shift, temp.end());

    return wiring == temp && turnover == rotor.turnover && name == rotor.name;
}

std::ostream& operator<<(std::ostream &out, const Rotor &rotor)
{
    out << "Rotor " << rotor.name << "\n";
    out << "Turnover: " << rotor.turnover << "\n";
    out << "Curent Position: " << rotor.wiring[0][0] << "\n";
    out << "Current Ring Setting: " << rotor.ring << "\n\n";
    out << "Wiring:\n";
    int i = 0;
    for(std::string wires: rotor.wiring)
    {

        out << wires[0] << " - " << wires[1] << "\n";
    }
    return out;
}

