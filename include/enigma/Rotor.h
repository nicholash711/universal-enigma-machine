#ifndef ROTOR_H
#define ROTOR_H

#include <array>

class Rotor
{
    private:
        std::array<std::string, 26> wiring;
        std::string turnover = "";
        char ring = 0;
        std::string name = "";

    public:
        Rotor();
        Rotor(Rotor& rotor);
        Rotor(std::string wiring, std::string turnover, std::string name);
        std::string getName();
        std::string getTurnover();
        std::array<std::string, 26> getWiring();
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
        bool operator==(Rotor &rotor);
        friend std::ostream& operator<<(std::ostream &out, const Rotor &rotor);
};

#endif