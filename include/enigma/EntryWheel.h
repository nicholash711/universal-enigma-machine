#ifndef ENTRYWHEEL_H
#define ENTRYWHEEL_H

#include <array>

class EntryWheel
{
    private:
        std::array<std::string, 26> wiring;

    public:
        EntryWheel();
        EntryWheel(EntryWheel& wheel);
        EntryWheel(std::string wire);
        char enterChar(char c);
};

#endif