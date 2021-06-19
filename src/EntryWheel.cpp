#include <enigma/EntryWheel.h>

EntryWheel::EntryWheel()
{
    for(int i = 0; i < 26; i++)
        wiring[0] = std::string() + (char)(i + 65) + (char)(i + 65);
}

EntryWheel::EntryWheel(std::string wire)
{
    for(int i = 0; i < 26; i++)
        wiring[0] = std::string() + (char)(i + 65) + wire[i];
}

char EntryWheel::enterChar(char c)
{
    return wiring[c - 65][1];
}