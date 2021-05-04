#include <iostream>
#pragma once

using namespace std;

class Spell{
    private:
    const string name;
    const int price;
    const int minLevel;
    const int damageFactor;
    const int reqMagicPower;
    const int dmgLimiter; // Monster Damage Limiter
    const int defLimiter; // Monster Defence Limiter
    const int dexLimiter; // Monster Dexterity Limiter

    public:
    Spell(string name, int price, int minLevel, int damageFactor, int reqMagicPower, int dmgLimiter, int defLimiter, int dexLimiter)
        :name(name),
        price(price),
        minLevel(minLevel),
        damageFactor(damageFactor),
        reqMagicPower(reqMagicPower),
        dmgLimiter(dmgLimiter),
        defLimiter(defLimiter),
        dexLimiter(dexLimiter)
        {}
    
    void get_attributes(int& dmgLimiter, int& defLimiter, int& dexLimiter) const{
        dmgLimiter = this->dmgLimiter;
        defLimiter = this->defLimiter;
        dexLimiter = this->dexLimiter;
    }

    virtual void printSpell() const{
        cout << "Spell name: " << this->name
            << "\n  Requirements:"
            << "\n    Min Level: " << this->minLevel
            << "\n  Required Magic Power: " << this->reqMagicPower
            << endl;
    }

    int get_dmgLimiter() const{
        return this->dmgLimiter;
    }

    int get_defLimiter() const{
        return this->defLimiter;
    }

    int get_dexLimiter() const{
        return this->dexLimiter;
    }

    int get_minLevel() const{
        return this->minLevel;
    }

    int getPrice() const{
        return this->price;
    }
    
    int get_reqMagicPower() const{
        return this->reqMagicPower;
    }

    int get_damageFactor(){
        return this->damageFactor;
    }

    string getName(){
        return this->name;
    }
    virtual ~Spell(){}
};

class IceSpell : public Spell{
    public:
    IceSpell(string name, int price, int minLevel, int damageFactor, int reqMagicPower, int monsterDamageLimiter):
    Spell(name, price, minLevel, damageFactor, reqMagicPower, monsterDamageLimiter, 0, 0)
    {

    }

    void printSpell() const{
        Spell::printSpell();
        cout << "Bonus: +" << get_dmgLimiter() << " Monster Damage Limiter" << endl;
    }

};

class FireSpell : public Spell{
    public:
    FireSpell(string name, int price, int minLevel, int damageFactor, int reqMagicPower, int defLimiter):
    Spell(name, price, minLevel, damageFactor, reqMagicPower, 0, defLimiter, 0)
    {

    }

    void printSpell() const{
        Spell::printSpell();
        cout << "Bonus: +" << get_defLimiter() << " Monster Defence Limiter" << endl;
    }
};

class LightningSpell : public Spell{
    public:
    LightningSpell(string name, int price, int minLevel, int damageFactor, int reqMagicPower, int dexLimiter):
    Spell(name, price, minLevel, damageFactor, reqMagicPower, 0, 0, dexLimiter)
    {

    }

    void printSpell() const{
        Spell::printSpell();
        cout << "Bonus: +" << get_dexLimiter() << " Monster Attack Avoidance Probability Limiter" << endl;
    }
};
