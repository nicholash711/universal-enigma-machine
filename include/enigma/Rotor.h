#ifndef ROTOR_H
#define ROTOR_H

#include <array>

class Rotor
{
    private:
        std::array<std::string, 26> wiring;
        char turnover;
        char ring;
        std::string name;

    public:
        Rotor();
        Rotor(std::string wire, char turn, std::string n);
        std::string getName();
        char getTurnover();
        char getCurrent();
        char getRing();
        int encrypt(char c);
        int encrypt(int c);
        int reencrypt(char c);
        int reencrypt(int c);
        bool rotate();
        bool setRotorPosition(char pos);
        bool setRingPosition(char pos);
        void reset();
        void operator=(Rotor &rotor);
        bool operator==(Rotor &rotor);
        friend std::ostream& operator<<(std::ostream &out, const Rotor &rotor);
};

#endif