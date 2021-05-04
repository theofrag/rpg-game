#include "Item.h"
#include "Spell.h"
#include <vector>

const static int MAX_WEAPONS=10;
const static int MAX_ARMORS=10;
const static int MAX_POTIONS=10;
const static int MAX_SPELLS=10;


class Inventory {

private:
    vector <Weapon*> weapons; // Τα οπλα που ειναι αποθηκευμενα στο inventory
    vector <Armor*> armors;   // Armors που ειναι αποθηκευμενες στο inventory
    vector <Potion*> potions; // Tα potions που ειναι αποθηκευμενα στο inventory
    vector <Spell*> spells;

    //Default τιμες, μεγιστης χωρητικοτητας του inventory
    unsigned int maxWeapons;
    unsigned int maxArmors;
    unsigned int maxPotions;
    unsigned int maxSpells;

public:
    Inventory():maxWeapons(MAX_WEAPONS), maxArmors(MAX_ARMORS), maxPotions(MAX_POTIONS), maxSpells(MAX_SPELLS){}
    
    //Aποθηκευει ενα weapon/armor/potion στο inventory
    void store(Weapon&);
    void store(Armor& );
    void store(Potion& );
    void store(Spell& );

    //Aφαιρει το item απο το inventory και επιστρεφει τον δεικτη στο item αυτο
    Weapon* discardWeapon(string);
    Armor* discardArmor(string);
    Potion* discardPotion(string);
    Spell* discardSpell(string);

    // GETTERS
    Potion* getPotion(string name);
    Spell* getSpell(string name);
    Weapon* getWeapon(string name);
    Armor* getArmor(string name);

    void printWeapons();    //εκτυπωνει μονο τα weapons του inventory
    void printArmor();  //εκτυπωνει μονο τα armors του inventory
    void printPotions();    //εκτυπωνει μονο τα potions του inventory
    void printSpells();
    void printInventory();  //εκτυπωνει τα παντα

    ~Inventory();

};



//Equipment συμβολιζει τον εξοπλισμο που εχει κανει equip ο ηρωας καθε χρονικη στιγμή.
class Equipment{

private:
    //Aν το weapon ειναι 2 handed, τοτε το lefthand θα δειχνει οπου και το righthand
    Weapon* rightHand;
    Weapon* leftHand;
    Armor* armor;

public:
    Equipment(): 
        rightHand(NULL), 
        leftHand(NULL), 
        armor(NULL){}

    //Προσθετει στο equipment
    void add(Armor& armor);
    //Προσθετει οπλο στο equipment, στο χερι που  υποδεικνύεται
    void add(Weapon& weapon,string hand);

    
    Weapon* getRightWeapon();
    Weapon* getLeftWeapon();
    Armor* getArmor();

    //Aφαιρει απο το equipemnt 
    Weapon* unequipRightWeapon();
    Weapon* unequipLeftWeapon();
    Armor* unequipArmor();

    //κανει print το equipment
    void print();

    ~Equipment();
};