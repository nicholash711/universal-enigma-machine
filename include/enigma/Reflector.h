#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <string>
#include <array>

class Reflector
{
    private:
        std::array<char, 26> reflector;
        std::string name;
    public:
        Reflector();
        Reflector(Reflector& ref);
        Reflector(std::string wiring, std::string n);
        std::string getName();
        int reflect(char c);
        int reflect(int c);
        void operator=(Reflector &reflector);
        friend std::ostream& operator<<(std::ostream &out, Reflector &reflector);
};

#endif