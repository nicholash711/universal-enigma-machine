#include <enigma/EntryWheel.h>
#include <iostream>

EntryWheel::EntryWheel()
{
    wiring = std::string();
    for(int i = 0; i < 26; i++)
        wiring += (char)(i + 65);
}

EntryWheel::EntryWheel(EntryWheel& wheel)
{
    this->wiring = wheel.wiring;
}

EntryWheel::EntryWheel(std::string wire)
{
    wiring = wire;
}

char EntryWheel::enterChar(char c)
{
    return wiring[c - 65];
}

char EntryWheel::reenterChar(char c)
{
    for(int i = 0; i < 26; i++)
        if(wiring[i] == c)
        {
            return i + 65;
        }
            
    return 0;
}

std::ostream& operator<<(std::ostream &out, EntryWheel& wheel)
{
    out << wheel.wiring << std::endl;
    return out;
}