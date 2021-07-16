#ifndef ENIGMA_H
#define ENIGMA_H

#include <array>
#include <vector>
#include <enigma/Rotor.h>
#include <enigma/Reflector.h>
#include <enigma/Plugboard.h>
#include <enigma/EntryWheel.h>

class Enigma
{
    private:
        std::array<Rotor*, 3> rotors;
        Rotor* rotor4;
        Plugboard* plugboard;
        Reflector* reflector;
        EntryWheel* entry;
        bool doDouble;

        char rotorEncryption(char c);
        void rotateRotors();
        char encryptChar(char c);

    public:
        Enigma();
        Enigma(Enigma& enigma);
        std::array<Rotor*, 3> getRotors();
        Reflector* getReflector();
        Plugboard* getPlugboard();
        EntryWheel* getEntryWheel();
        std::string encrypt(std::string mes);
        void setRotor(Rotor& rot, int i);
        void setRotor(std::string wiring, std::string turnover, std::string name, int i);
        bool setPlugs(std::vector<std::string> plugs);
        bool setPlug(std::string plug);
        void setReflector(Reflector& ref);
        void setEntryWheel(EntryWheel& entry);
        void setEntryWheel(std::string wiring);
        bool setPosition(char c, int pos);
        bool setRing(char c, int pos);
        bool clearRotor(int i);
        void doesDouble(bool doub);
        friend std::ostream& operator<<(std::ostream &out, Enigma &engima);
};

#endif