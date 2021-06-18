#include <iostream>
#include <cmath>
#include <algorithm>
#include <enigma/Rotor.h>

Rotor::Rotor()
{
    name = "";
    turnover = 0;
    wiring.fill("");
}

Rotor::Rotor(std::string wire, char turn, std::string n)
{
    name = n;
    turnover = toupper(turn);
    for(int i = 0; i < 26; i++)
        wiring[i] = std::string() + (char)(i + 65) + (char)toupper(wire[i]) + (char)(i + 65);
}

std::string Rotor::getName()
{
    return name;
}

char Rotor::getTurnover()
{
    return turnover;
}

char Rotor::getCurrent()
{
    return wiring[0][0];
}

char Rotor:: getRing()
{   
    int shift = ('A' - wiring[0][0] + 26 ) % 26;
    return wiring[shift][2];
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
            return i;
    }
    return -1;
}

int Rotor::reencrypt(int c)
{
    char encrypt = wiring[c][0];
    for(int i = 0; i < 26; i++)
    {
        if(wiring[i][1] == encrypt)
            return i;
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
    return wiring[25][0] == turnover;
}

bool Rotor::setRotorPosition(char pos)
{
    if(!std::isalpha(pos))
        return false;
    pos = toupper(pos);
    char current = wiring[0][0];
    int shift = (pos - current + 26) % 26;
    std::rotate(wiring.begin(), wiring.begin() + shift, wiring.end());
    return true;
}

bool Rotor::setRingPosition(char pos)
{
    if(!std::isalpha(pos))
        return false;
    pos = toupper(pos);
    std::array<std::string, 26> temp;
    int shift = (pos - 'A' + 26) % 26;
    std::transform(wiring.begin(), wiring.end(), temp.begin(), 
        [](std::string chars){ return chars.substr(1, 2); });
    std::rotate(temp.begin(), temp.begin() + shift, temp.end());
    for(int i = 0; i < 26; i++)
        wiring[i][1] = (temp[i][0] - shift + 26) % 26, wiring[i][2] = temp[i][1];
    return true;

}

void Rotor::reset()
{
    setRingPosition('A');
    setRotorPosition('A');
}

void Rotor::operator=(Rotor &rotor)
{
    name = rotor.name;
    turnover = rotor.turnover;
    wiring = rotor.wiring;
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
    out << "Curent Position: " << rotor.wiring[0][0] << "\n\n";
    out << "Wiring:\n";
    int i = 0;
    for(std::string wires: rotor.wiring)
    {

        out << wires[0] << " - " << wires[1] << "\n";
    }
    return out;
}

