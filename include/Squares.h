#include <iostream>
#include <vector>
#include "Living.h"


using namespace std;
//Tα squares απο τα οποια θα αποτελειται το Grid
// Θα ειναι abstract κλαση

class NullSquare {

protected:
    Hero* heroes[3];
public:
    NullSquare(){
        for(int i=0;i<3;i++)
            this->heroes[i]=NULL;
    }

    // -1 = nonAccesible square, 0 = common, 1 = market
    virtual int get_id()=0;  

//! pure virtual απο εδω και κατω

//Προσθέτει εναν πίνακα ηρωων στο συγκεκριμενο square.
    virtual void addHeroes(Hero** h)=0;

//Aφαιρει τους ηρωες απο το συγκεκριμενο square
    virtual void removeHeroes()=0;

    virtual bool  hasMarket()=0;

    //Aφαιρει ενα item απο το συγκεκριμενο square
    virtual Weapon* discardWeapon(string weaponName)=0;  
    virtual  Armor* discardArmor(string ArmorName)=0;
    virtual  Potion* discardPotion(string PotionName)=0;
    virtual  Spell* discardSpell(string spellName)=0;

    //Προσθετει items στο συγκεκριμενο square
    virtual void add(Weapon& weapon)=0;
    virtual  void add(Armor& armor)=0;
    virtual  void add(Potion& potion)=0;
    virtual void add(Spell& spell )=0;

    virtual void print(){return;}
    virtual ~NullSquare(){}

};

//TODO
class Market : public NullSquare{

private:
    vector <Weapon*> weapons; 
    vector <Armor*> armors;   
    vector <Potion*> potions; 
    vector <Spell*> spells; 

public:
    int get_id(){ return 1;}

    Weapon* discardWeapon(string weaponName);
    Armor* discardArmor(string ArmorName);
    Potion* discardPotion(string PotionName);
    Spell* discardSpell(string spellName);
    
    void add(Weapon& weapon);
    void add(Armor& armor);
    void add(Potion& potion);
    void add(Spell& spell );

    //Οι remove/addHeroes βάζουν τους ηρωες στο συγκεκριμενο τετραγωνακι
    void addHeroes(Hero** h){
        heroes[0]=h[0];
        heroes[1]=h[1];
        heroes[2]=h[2];
    }
    void removeHeroes(){
        heroes[0]=NULL;
        heroes[1]=NULL;
        heroes[2]=NULL;
    }


    bool hasMarket(){return true;}
    void print();  //κανει print τα παντα
    ~Market();

};

//TODO
class NonAccessible: public NullSquare{

public:

    int get_id(){ return -1;}

    void addHeroes(Hero** h){
        cout<<"You dont have access here"<<endl;
    }
    void removeHeroes(){
        cout<<"You dont have access here"<<endl;
    }

    bool hasMarket(){ return false; }
    
    Weapon* discardWeapon(string weaponName){cout<<"There is no shop here"<<endl; return NULL;}
    Armor* discardArmor(string ArmorName){cout<<"There is no shop here"<<endl; return NULL;}
    Potion* discardPotion(string PotionName){cout<<"There is no shop here"<<endl; return NULL; }
    Spell* discardSpell(string spellName){cout<<"There is no shop here"<<endl; return NULL; }


    void add(Weapon& weapon){cout<<"There is no shop here"<<endl;}
    void add(Armor& armor){cout<<"There is no shop here"<<endl;}
    void add(Potion& potion){cout<<"There is no shop here"<<endl;}
    void add(Spell& spell){cout<<"There is no shop here"<<endl;}

};

class Common: public NullSquare{

public:

    int get_id(){ return 0;}
    
    void addHeroes(Hero** h){
        heroes[0]=h[0];
        heroes[1]=h[1];
        heroes[2]=h[2];
    }
    void removeHeroes(){
        heroes[0]=NULL;
        heroes[1]=NULL;
        heroes[2]=NULL;
    }
    
    bool hasMarket(){ return false; }
    Weapon* discardWeapon(string weaponName){cout<<"There is no shop here"<<endl;return NULL;}
    Armor* discardArmor(string ArmorName){cout<<"There is no shop here"<<endl;return NULL;}
    Potion* discardPotion(string PotionName){cout<<"There is no shop here"<<endl;return NULL;}
    Spell* discardSpell(string spellName){cout<<"There is no shop here"<<endl; return NULL; }

    
    void add(Weapon& weapon){cout<<"There is no shop here"<<endl;}
    void add(Armor& armor){cout<<"There is no shop here"<<endl;}
    void add(Potion& potion){cout<<"There is no shop here"<<endl;}
    void add(Spell& spell){cout<<"There is no shop here"<<endl;}
};

