#include <iostream>

using namespace std;

class Item{

private:
    string name;
    int minLevel;  //ελαχιστο επιπεδο που πρεπει να βρισκεται καποιος για να το χρησιμοποιησει
    int price;

public:
    Item(string name, int minLevel=1, int price=100):
        name(name),minLevel(minLevel),price(price) {}
         
    string getName(){return this->name;}
    int getPrice(){return this->price;}
    int get_minLevel(){return this->minLevel;}
    virtual void printItem()=0;
    virtual ~Item(){}
};

//!ABSTRACT
//Ειναι abstract γιατι καθε οπλο χωριζεται σε δυο κατηγοριες: twoHandWeapon και oneHandWeapon
class Weapon: public Item {

private:
    int attackDamage;
 
public:
    Weapon(string name, int minLevel=1,int price=100,int dmg=5):
        Item(name,minLevel,price), attackDamage(dmg) {}
    
    //Επιστρεφει true αν ειναι οπλο για ένα χέρι, αλλίως επιστρέφει false
    virtual bool isOneHandWeapon()=0;
    int getDamage(){return this->attackDamage;}
    virtual ~Weapon(){}
};

class OneHandWeapon: public Weapon{

public:
    OneHandWeapon(string name, int minLevel=1,int price=100, int dmg=5): 
        Weapon(name,minLevel,price,dmg){}
    
    bool isOneHandWeapon(){ return true;}
    void printItem(){
        cout<<"OneHandWeapon name: "<<this->getName()<<"\n"
        <<"  Requirements: \n"
        <<"    Min Level to use this weapon: "<<this->get_minLevel()<<"\n"
        <<"  Bonus: +"<<this->getDamage()<<" attack damage"<<endl;    
    }
    

};

class TwoHandWeapon: public Weapon{


public:
    TwoHandWeapon(string name, int minLevel=1,int price=100, int dmg=5): 
        Weapon(name,minLevel,price,dmg){}
    
    bool isOneHandWeapon(){ return false;}

    void printItem(){
        cout<<"TwoHandWeapon name: "<<this->getName()<<"\n"
        <<"  Requirements: \n"
        <<"    Min Level to use this weapon: "<<this->get_minLevel()<<"\n"
        <<"  Bonus: +"<<this->getDamage()<<" attack damage"<<endl;    
    }

};


class Armor: public Item {

private:
    int resistance;

public:
    Armor(string name, int minLevel=1, int price=100, int res=5):
        Item(name,minLevel,price), resistance(res){}
    
    int getResistance(){ return this->resistance; }

    public:
    void printItem(){
        cout<<"Armor name: "<<this->getName()<<"\n"
        <<"  Requirements: \n"
        <<"    Min Level to use this Amor: "<<this->get_minLevel()<<"\n"
        <<"  Bonus: +"<<this->getResistance()<<" armor"<<endl;    
    }

};


class Potion: public Item{

private:
    int strenghtBoost;
    int dexterityBoost;
    int agilityBoost;
    bool used;
public:
    Potion(string name,int minLevel,int price,int str, int dex, int agil):
        Item(name,minLevel,price), 
        strenghtBoost(str), 
        dexterityBoost(dex), 
        agilityBoost(agil),
        used(false){}

    //Επιστρεφει στα str,dex,agil το ποσο που αυξανει το dexterity/strenght/agility , το potion
    void get_attributes(int& str,int& dex,int& agil){
        str=this->get_strenght();
        dex=this->get_dexterity();
        agil=this->get_agility();
    }

    int get_strenght(){return this->strenghtBoost;}
    int get_dexterity(){return this->dexterityBoost;}
    int get_agility(){return this->agilityBoost;}

    void usePotion(){
        this->used=true;
    }

    //Eπιστρεφει false αν το pottion δεν εχει χρησιμοποιηθει, αλλιως true
    bool getUsed(){return this->used;}

};

//Potion που αυξανει το strenght
class StrenghtPotion: public Potion{

public:
    StrenghtPotion(string name,int minLevel,int price, int str):
        Potion(name,minLevel,price,str,0,0){}
    
    void printItem(){
        cout<<"Potion name: "<<this->getName()<<"\n"
        <<"  Requirements: \n"
        <<"    Min Level to use this potion: "<<this->get_minLevel()<<"\n"
        <<"  Bonus: +"<<this->get_strenght()<<" attack damage"<<endl;    
    }
};

//Potion που αυξανει το dexterity
class DexterityPotion: public Potion{

public:

    DexterityPotion(string name,int minLevel,int price, int dxt):
        Potion(name,minLevel,price,0,dxt,0){}

    void printItem(){
        cout<<"Potion name: "<<this->getName()<<"\n"
        <<"  Requirements: \n"
        <<"    Min Level to use this potion: "<<this->get_minLevel()<<"\n"
        <<"  Bonus: +"<<this->get_dexterity()<<" dexterity"<<endl;    
    }


};

//Potion που αυξανει το dexterity
class AgilityPotion: public Potion{

public:
    AgilityPotion(string name,int minLevel,int price, int agl):
        Potion(name,minLevel,price,0,0,agl){}

    void printItem(){
        cout<<"Potion name: "<<this->getName()<<"\n"
        <<"  Requirements: \n"
        <<"    Min Level to use this potion: "<<this->get_minLevel()<<"\n"
        <<"  Bonus: +"<<this->get_agility()<<" agility"<<endl;    
    }

};


