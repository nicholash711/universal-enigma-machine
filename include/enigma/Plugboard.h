#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <array>

class Plugboard
{
    private:
        std::array<char, 26> plugboard;
        int plugs;
    public:
        Plugboard();
        Plugboard(Plugboard& plug);
        std::string getPlugs();
        bool addPlug(std::string pair);
        bool removePlug(char c);
        char encrypt(char c);
        void clear();
        void operator=(Plugboard &plugboard);
        friend std::ostream& operator<<(std::ostream &out, Plugboard &plugboard);
};

#endif