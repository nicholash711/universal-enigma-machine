#ifndef ROTOR_H
#define ROTOR_H

#include <array>

class Rotor
{
    private:
        std::array<std::string, 26> wiring;
        std::string turnover;
        char ring;
        std::string name;

    public:
        Rotor();
        Rotor(Rotor& rotor);
        Rotor(std::string wiring, std::string turnover, std::string name);
        std::string getName();
        std::string getTurnover();
        char getCurrent();
        char getRing();
        int encrypt(char c);
        int encrypt(int c);
        int reencrypt(char c);
        int reencrypt(int c);
        bool rotate();
        bool setRotorPosition(char pos);
        bool setRingSetting(char pos);
        void reset();
        // void operator=(Rotor& rotor);
        bool operator==(Rotor &rotor);
        friend std::ostream& operator<<(std::ostream &out, const Rotor &rotor);
};

#endif