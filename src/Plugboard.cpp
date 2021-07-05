#include <iostream>
#include <enigma/Plugboard.h>

Plugboard::Plugboard()
{
    plugboard.fill(0);
    plugs = 0;
}

Plugboard::Plugboard(Plugboard& plug)
{
    this->plugboard = plug.plugboard;
    this->plugs = plug.plugs;
}

bool Plugboard::isAlpha(std::string str)
{
    for(char c : str)
        if(!isalpha(c))
            return false;
    return true;
}

std::string Plugboard::getPlugs()
{
    std::string str = std::string();

    for(int i = 0; i < 26; i++)
        if(str.find(i + 65) == -1 && plugboard[i] != 0)
            str += std::string() + (char)(i + 65) + plugboard[i] + " ";
    return str;
}

bool Plugboard::addPlug(std::string pair)
{   
    if(plugs == 10 || pair.size() != 2 || !isAlpha(pair))
        return false;
    char first = toupper(pair[0]), second = toupper(pair[1]);
    if(plugboard[first - 65] == plugboard[second - 65])
    {
        plugboard[first - 65] = second;
        plugboard[second - 65] = first;
        plugs += 1;
        return true;
    }
    else
        return false;
}

bool Plugboard::removePlug(char c)
{
    c = toupper(c);
    if(plugboard[c - 65] == 0)
        return false;
    else
    {
        char connection = plugboard[c - 65];
        plugboard[c - 65] = 0;
        plugboard[connection - 65] = 0;
        plugs -= 1;
        return true;
    }
}

char Plugboard::encrypt(char c)
{
    c = toupper(c);
    if(plugboard[c - 65] == 0)
        return c;
    return plugboard[c - 65];
}

void Plugboard::clear()
{
    plugboard.fill(0);
    plugs = 0;
}

void Plugboard::operator=(Plugboard &plugboard)
{
    Plugboard::plugboard = plugboard.plugboard;
}

std::ostream& operator<<(std::ostream &out, Plugboard &plugboard)
{
    std::string str = std::string();

    for(int i = 0; i < 26; i++)
        if(str.find(i + 65) == -1 && plugboard.plugboard[i] != 0)
            str += std::string() + (char)(i + 65) + plugboard.plugboard[i] + " ";
    out << str;
    return out;
}

void Plugboard::showArray()
{
    for(int i = 0; i < 26; i++)
        std::cout << (char)(i + 65) << " - " << (int)plugboard[i] << std::endl;
}