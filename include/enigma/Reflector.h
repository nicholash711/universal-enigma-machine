#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <string>
#include <array>

class Reflector
{
    private:
        std::array<std::string, 26> reflector;
        std::string name;
        char ring;
        bool rotatable;

    public:
        Reflector();
        Reflector(Reflector& ref);
        Reflector(std::string wiring, std::string name);
        std::string getName();
        int reflect(char c);
        int reflect(int c);
        bool isRotatable();
        char getCurrent();
        char getRing();
        void setRotatable(bool rotate);
        void setReflectorPosition(char c);
        void setRingPosition(char c);
        void rotate();
        void operator=(Reflector &reflector);
        friend std::ostream& operator<<(std::ostream &out, Reflector &reflector);
};

#endif