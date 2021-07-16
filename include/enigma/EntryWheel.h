#ifndef ENTRYWHEEL_H
#define ENTRYWHEEL_H

#include <string>

class EntryWheel
{
    private:
        std::string wiring;

    public:
        EntryWheel();
        EntryWheel(EntryWheel& wheel);
        EntryWheel(std::string wire);
        char enterChar(char c);
        char reenterChar(char c);
        friend std::ostream& operator<<(std::ostream &out, EntryWheel& wheel);
};

#endif