#include <iostream>
#include <enigma/Enigma.h>

Enigma::Enigma()
{
    
}

char Enigma::rotorEncryption(char c)
{
    int encrypted = rotors[0].encrypt(rotors[1].encrypt(rotors[2].encrypt(c)));
    encrypted = reflector.reflect(encrypted);
    encrypted = rotors[2].reencrypt(rotors[1].reencrypt(rotors[0].reencrypt(encrypted)));
    return encrypted + 65;

}
void Enigma::rotateRotors()
{
    if(rotors[2].rotate())
        if(rotors[1].rotate())
            rotors[0].rotate();
}

std::array<Rotor, 3> Enigma::getRotors()
{
    return rotors;
}

char Enigma::encryptChar(char c)
{
    rotateRotors();
    char encrypted = entry.enterChar(c);
    encrypted = plugboard.encrypt(c);
    encrypted = rotorEncryption(encrypted);
    encrypted = plugboard.encrypt(encrypted);
    
    return encrypted;
}

std::string Enigma::encrypt(std::string mes)
{
    std::string encrypted = std::string();
    for(int i = 0; i < mes.size(); i++)
    {
        if(mes[i] == 32)
            continue;
        encrypted += encryptChar(toupper(mes[i]));
        if(encrypted.size() % 6 == 5)
            encrypted += " ";
        
    }
        
    return encrypted;
}

bool Enigma::setRotor(Rotor rot, int i)
{
    for(Rotor rotor: rotors)
        if(rotor == rot)
            return false;
    rotors[i - 1] = rot;
    return true;
}

bool Enigma::setPlug(std::string plug)
{
    return plugboard.addPlug(plug);
}

void Enigma::setReflector(Reflector ref)
{
    reflector = ref;
}

void Enigma::setEntryWheel(EntryWheel entry)
{
    this->entry = entry;
}

bool Enigma::setPosition(char c, int i)
{
    return rotors[i - 1].setRotorPosition(c);
}

bool Enigma::setRing(char c, int i)
{
    return rotors[i - 1].setRingSetting(c);
}

bool Enigma::clearRotor(int i)
{
    Rotor empty;
    if(i < 1 || i > 3)
        return false;
    rotors[i - 1] = empty;
    return true;
}

std::ostream& operator<<(std::ostream &out, Enigma &enigma)
{
    out << "Plugboard: " << enigma.plugboard <<"\n";
    out << "Rotors: " << enigma.rotors[0].getName() << " " << enigma.rotors[1].getName() << " " << enigma.rotors[2].getName() << "\n";
    out << "Rotor Settings: " << enigma.rotors[0].getCurrent() << " " << enigma.rotors[1].getCurrent() << " " << enigma.rotors[2].getCurrent() << "\n";
    out << "Ring Settings: " << enigma.rotors[0].getRing() << " " << enigma.rotors[1].getRing() << " " << enigma.rotors[2].getRing() << "\n";
    out << "Reflector: " << enigma.reflector.getName();
    return out;
}