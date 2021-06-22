#ifndef ENIGMA_H
#define ENIGMA_H

#include <array>
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

        char rotorEncryption(char c);
        void rotateRotors();
        char encryptChar(char c);

    public:
        Enigma();
        std::array<Rotor*, 3> getRotors();
        Reflector* getReflector();
        Plugboard* getPlugboard();
        EntryWheel* getEntryWheel();
        std::string encrypt(std::string mes);
        void setRotor(Rotor& rot, int pos);
        bool setPlug(std::string plug);
        void setReflector(Reflector& ref);
        void setEntryWheel(EntryWheel& entry);
        bool setPosition(char c, int pos);
        bool setRing(char c, int pos);
        bool clearRotor(int i);
        friend std::ostream& operator<<(std::ostream &out, Enigma &engima);
};

#endif