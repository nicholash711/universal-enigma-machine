#include <iostream>
#include <enigma/Enigma.h>

Enigma::Enigma()
{
    for(int i = 0; i < 3; i++)
        rotors[i] = new Rotor();
    rotor4 = new Rotor();
    plugboard = new Plugboard();
    reflector = new Reflector();
    entry = new EntryWheel();
    doDouble = true;
}

Enigma::Enigma(Enigma& enigma)
{
    rotors = enigma.rotors;
    rotor4 = enigma.rotor4;
    plugboard = enigma.plugboard;
    reflector = enigma.reflector;
    entry = enigma.entry;
}

char Enigma::rotorEncryption(char c)
{
    int encrypted = rotors[0]->encrypt(rotors[1]->encrypt(rotors[2]->encrypt(c)));
    encrypted = reflector->reflect(encrypted);
    encrypted = rotors[2]->reencrypt(rotors[1]->reencrypt(rotors[0]->reencrypt(encrypted)));
    return encrypted + 65;

}
void Enigma::rotateRotors()
{
    if(rotors[2]->rotate())
        if(rotors[1]->rotate())
            if(rotors[0]->rotate() && reflector->isRotatable())
                reflector->rotate();

    if(doDouble && rotors[1]->getTurnover().find(rotors[1]->getCurrent()) != std::string::npos)
    {
        rotors[1]->rotate();
        rotors[0]->rotate();
    }
}

std::array<Rotor*, 3> Enigma::getRotors()
{
    return rotors;
}

Reflector* Enigma::getReflector()
{
    return reflector;
}

Plugboard* Enigma::getPlugboard()
{
    return plugboard;
}

EntryWheel* Enigma::getEntryWheel()
{
    return entry;
}

char Enigma::encryptChar(char c)
{
    rotateRotors();
    char encrypted = entry->enterChar(c);
    encrypted = plugboard->encrypt(encrypted);
    encrypted = rotorEncryption(encrypted);
    encrypted = plugboard->encrypt(encrypted);
    encrypted = entry->reenterChar(encrypted);
    
    
    return encrypted;
}

std::string Enigma::encrypt(std::string mes)
{
    std::string positions = std::string();
    for(Rotor* rot : rotors)
        positions += rot->getCurrent();
    positions += reflector->getCurrent();
    std::string encrypted = std::string();
    for(int i = 0; i < mes.size(); i++)
    {
        if(isalpha(mes[i]))
            encrypted += encryptChar(toupper(mes[i]));
        if(encrypted.size() % 6 == 5)
            encrypted += " ";
        
    }
    for(int i = 0; i < 3; i++)
    {
        rotors[i]->setRotorPosition(positions[i]);
    }
    reflector->setReflectorPosition(positions.back());
        
    return encrypted;
}

void Enigma::setRotor(Rotor& rot, int i)
{
    delete this->rotors[i];
    rotors[i] = new Rotor(rot);
}

void Enigma::setRotor(std::string wiring, std::string turnover, std::string name, int i)
{
    delete this->rotors[i];
    rotors[i] = new Rotor(wiring, turnover, name);
}
bool Enigma::setPlugs(std::vector<std::string> plugs)
{
    plugboard->clear();
    for(std::string plug : plugs)
    {
        if(!plugboard->addPlug(plug))
        {
            plugboard->clear();
            return false;
        }
    }
    return true;
}

bool Enigma::setPlug(std::string plug)
{
    return plugboard->addPlug(plug);
}

void Enigma::setReflector(Reflector& ref)
{
    delete this->reflector;
    reflector = new Reflector(ref);
}

void Enigma::setEntryWheel(EntryWheel& entry)
{
    delete this->entry;
    this->entry = new EntryWheel(entry);
}

void Enigma::setEntryWheel(std::string wiring)
{
    delete this->entry;
    this->entry = new EntryWheel(wiring);
}

bool Enigma::setPosition(char c, int i)
{
    return rotors[i]->setRotorPosition(c);
}

bool Enigma::setRing(char c, int i)
{
    return rotors[i]->setRingSetting(c);
}

bool Enigma::clearRotor(int i)
{
    if(i < 0 || i > 2)
        return false;
    rotors[i] = new Rotor();
    return true;
}

void Enigma::doesDouble(bool doub)
{
    doDouble = doub;
}

std::ostream& operator<<(std::ostream &out, Enigma &enigma)
{
    out << "\nPlugboard: " << *(enigma.plugboard);
    out << "\nRotors: ";
    if(enigma.rotor4 != nullptr)
        out << enigma.rotor4->getName() << " ";
    out << enigma.rotors[0]->getName() << " " << enigma.rotors[1]->getName() << " " << enigma.rotors[2]->getName();
    out << "\nRotor Settings: ";
    if(enigma.rotor4 != nullptr)
        out << enigma.rotor4->getCurrent() << " ";
    out << enigma.rotors[0]->getCurrent() << " " << enigma.rotors[1]->getCurrent() << " " << enigma.rotors[2]->getCurrent();
    out << "\nRing Settings: ";
    if(enigma.rotor4 != nullptr)
        out << enigma.rotor4->getRing() << " ";
    out << enigma.rotors[0]->getRing() << " " << enigma.rotors[1]->getRing() << " " << enigma.rotors[2]->getRing();
    out << "\nReflector: " << enigma.reflector->getName();
    if(enigma.reflector->isRotatable())
        out << " " << enigma.reflector->getCurrent() << " " << enigma.reflector->getRing() << std::endl;
    return out;
}