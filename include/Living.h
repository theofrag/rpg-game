#include <iostream>
#include "Randomness.h"
#include "Inventory.h"

using namespace std;

class Living {

private:
    string name;
    int level;         //starting from level 1
    int healthPower;    //scale:  100 + level*25
    
public:
    Living(string name,int level=1):
        name(name),
        level(level),
        healthPower(100 + level*25){}

    int getLevel()   { return this->level;      }
    string getName() { return this->name;       }
    int getHealth()  { return this->healthPower;}

    void reduceHealth(int dmg)  { this->healthPower-=dmg; } //μειωνει την ζωη κατα dmg
    void increaseHealth(int gen){ this->healthPower+=gen; } //αυξανει την ζωη κατα gen

};


class Hero: public Living {

protected:

    int magicPower;
    int strength;
    int dexterity;
    int agility;
    int money;
    int experience;  //1000 experience = new level
    bool occupied;  //Ειναι true οταν ο ηρωας ειναι σε διαδικασια sell/buy ή μαχεται
    Inventory inventory;    //Αποθηκη εξοπλισμου που εχει καθε ηθρωας
    Equipment equipment;    //Τα equipped οπλα του ηρωα

public:
    Hero(string name):
        Living(name),magicPower(100),
        strength(10),dexterity(10),agility(10),
        money(300),  experience(1000),occupied(false){}
    
    virtual ~Hero(){}

    void reduceMoney(int amount)  { money -= amount;}   //μειωνει τα χρηματα κατα amount
    void increaseMoney(int amount){ money += amount;}   //αυξανει τα χρηματα κατα amount
    void increaseExperience(int amount) { experience += amount;}
    int getMoney()      {return this->money;     }
    int getDexterity()  {return this->dexterity; }
    int getStrength()   {return this->strength;  }
    int getAgility()    {return this->agility;   }
    int getMagicPower() {return this->magicPower;}
    int getExperience() {return this->experience;}

    //Κανει print , όλα τα items που υπαρχουν στο inventory
    void checkInventory(); 

    //Προσθέτει ένα item στο inventory
    //Overloaded functions 
    void addToInventory(Weapon&);
    void addToInventory(Armor& );
    void addToInventory(Potion& );
    void addToInventory(Spell& );
    
    //Aφαιρει ενα weapon απο το inventory και επιστρεφει
    //ενα δεικτη στον τυπου του item που αφαιρεσε.
    Weapon* removeWeaponFromInventory( string name );
    Armor*  removeArmorFromInventory( string name );
    Potion* removePotionFromInventory( string name );
    Spell* removeSpellFromInventory(string name);

    //Κανει equip ενα weapon απο το inventory  απο το χερι <hand>
    void equipWeapon(string weaponName, string hand);
    //Κανε unequip ενα weapon απο το χέρι <hand> και το βαζει στο inventory
    void unequipWeapon(string hand);

    //Κάνει equip μια armor απο το inventory
    void equipArmor(string armor);

    //Αφαιρει την equipped armor και την βαζει στο inventory
    void unequipArmor();


    void use(Potion&);

    //Eπιστρεφει το equipped weapon απο το χερι <hand> (αριστερο ή δεξι)
    Weapon* getEquippedWeapon(string hand);

    //Επιστρεφει την equipped armor
    Armor* getEquippedArmor();


//Σε καθε lvl up , τα attributes αυξανονται συνολικα κατα 9
    virtual void levelUp(){

        //Υπολογίζω αν πρεπει να γινει lvl up. Καθε level αντιστοιχει σε 1000exp.
        //Για να μπορεσει ενας παικτης να ανεβει level, θα πρεπει exp να ειναι exp = level*1000 + x, οπου x>0
        //Πχ:  αν ενας ηρωας εχει 4500 exp και ειναι level 3, μπορει να ανεβει level.
        //Αν έχει 4500 exp και ειναι level 4, δεν μπορει.
        int temp= this->experience % (this->getLevel()*1000);
        int diff= temp / 1000 ;
        if(diff<1){
            cout<<"You need "<<1000 - temp<<" exp to level up"<<endl;
        }

        //Αν το dif ειναι ακεραιος μεγαλυτερος του 1(δηλαδη 2,3,4,.....,n), τοτε ο ηρωας ανεβαίνει n levels.
        for(int i=0;i<diff;i++){
            this->strength+=3;
            this->dexterity+=3;
            this->agility+=3;
        }
        
    }
   
    

    int getWeaponDamage(){

        Weapon* wp_l= equipment.getLeftWeapon();
        Weapon* wp_r= equipment.getRightWeapon();

        if(wp_l != NULL && !wp_l->isOneHandWeapon()){
            return wp_l->getDamage();
        }

        int result = 0;
        if(wp_l != NULL){
            result += wp_l->getDamage();
        }
        if(wp_r != NULL){
            result += wp_r->getDamage();
        }
        return result;
    }


    void printHeroSpells(){
        inventory.printSpells();
    }


    void printHeroPotions(){
        inventory.printPotions();
    }


    Potion* get_potion(string potion){
        return inventory.getPotion(potion);
    }


    Spell* get_spell(string sp){
        return inventory.getSpell(sp);
    }


    void increaseMagicPower(int amount){
        this->magicPower += amount;
    }


    void reduceMagicPower(int amount){
        this->magicPower -= amount;
    }

};

//Ενας warrior αρχιζει με 13 str, 12 agility , 10 dex
class Warrior: public Hero {

private:

public:
    Warrior(string name):Hero(name){
        this->strength+=3;
        this->agility+=2;
    }
    void levelUp(){
        int temp= this->experience % (this->getLevel()*1000);
        int diff= temp / 1000 ;
        if(diff<1){
            cout<<"You need "<<1000- temp<<" exp to level up"<<endl;
            return;
        }
    
        for(int i=0;i<diff;i++){
            this->strength+=4;
        this->dexterity+=2;
        this->agility+=3;
        }
    }
};



//Ενας sorcerer αρχιζει με 10 str, 13 agility, 12 dex
class Sorcerer: public Hero {

private:

public:
    Sorcerer(string name):Hero(name){
        this->dexterity+=2;
        this->agility+=3;
    }
    void levelUp(){
        int temp= this->experience % (this->getLevel()*1000);
        int diff= temp / 1000 ;
        if(diff<1){
            cout<<"You need "<<1000- temp<<" exp to level up"<<endl;
            return;
        }
    
        for(int i=0;i<diff;i++){
            this->strength+=2;
            this->dexterity+=3;
            this->agility+=4;
        }
    }
    
};

//Ενας paladin αρχιζει με 12 str, 13 dex, 10 agility
class Paladin: public Hero {

private:

public:
    Paladin(string name):Hero(name){
        this->dexterity+=3;
        this->strength+=2;
    }

    void levelUp(){
        int temp= this->experience % (this->getLevel()*1000);
        int diff= temp / 1000 ;
        if(diff<1){
            cout<<"You need "<<1000- temp<<" exp to level up"<<endl;
            return;
        }
    
        for(int i=0;i<diff;i++){
            this->strength+=3;
            this->dexterity+=4;
            this->agility+=2;
        }
    }
};

// ****************************************************************************


class Monster : public Living{
    private:
    int damageLimiterPercent;
    int damageLimiterRounds;
    int r_aaProbability; // reduced avoid attack probability
    int aaLimiterRounds;

    protected:
    int attackDamage;
    int avoidAttackProbability;

    public:
    Monster(string name, int level = 1);
    
    int getAttackDamage();
    bool receiveAttack(int damage);

    // Βάζει ένα ποσοστιαίο όριο (percent) στο βαθμό της ζημιάς που
    // μπορεί να προκαλέσει το τέρας, για (rounds) αριθμό γύρων
    void enableDamageLimiter(int percent, int rounds){
        this->damageLimiterPercent = percent;
        this->damageLimiterRounds = rounds;
    }

    // Μειώνει την πιθανότητα αποφυγής επίθεσης κατά (percent)
    // τοις εκατό για (rounds) αριθμό γύρων
    void reduceAAProbability(int percent, int rounds){
        this->r_aaProbability = percent;
        this->aaLimiterRounds = rounds;
    }

    void get_stats(int& damageLimiterPercent, int& damageLimiterRounds, int& r_aaProbability,
        int& aaLimiterRounds, int& attackDamage, int& avoidAttackProbability){

            damageLimiterPercent = this->damageLimiterPercent;
            damageLimiterRounds = this->damageLimiterRounds;
            r_aaProbability = this->r_aaProbability;
            aaLimiterRounds = this->aaLimiterRounds;
            attackDamage = this->attackDamage;
            avoidAttackProbability = this->avoidAttackProbability;
    }
};

class Dragon : public Monster{
    public:
    Dragon(string name, int level = 1);
};

class Exosceleton : public Monster{
    public:
    Exosceleton(string name, int level = 1);
};

class Spirit : public Monster{
    public:
    Spirit(string name, int level = 1);
};

Monster* get_random_monster(int);
