#include "Living.h"


void Hero::addToInventory(Weapon& weapon){
    this->inventory.store(weapon);
}

void Hero::addToInventory(Armor& armor){
    this->inventory.store(armor);
}

void Hero::addToInventory(Potion& potion){
    this->inventory.store(potion);
}

void Hero:: addToInventory(Spell& spell){
    this->inventory.store(spell);
}

Weapon* Hero::removeWeaponFromInventory(string name){
    return this->inventory.discardWeapon(name);
}

Armor* Hero::removeArmorFromInventory(string name){
    return this->inventory.discardArmor(name);
}

Potion* Hero::removePotionFromInventory(string name){
    return this->inventory.discardPotion(name);
}

Spell* Hero::removeSpellFromInventory(string name){
    return this->inventory.discardSpell(name);
}


void Hero::checkInventory(){

//Για να ελενξει καποιος το inventory δεν θα πρεπει να ειναι
//σε διαδικασια buy/sell ή σε μαχη.
    if(this->occupied){
        cout<<"Cant check the inventory now"<<endl;
        return;
    }

    cout<<"Inventory:"<<endl;
    this->equipment.print();

    //Απλα print για τα weapons, armors, potions που εχει ενας ηρωας στο inventory
    cout<<"Weapons stored are: "<<endl;
    this->inventory.printWeapons();

    cout<<"Armors stored are: "<<endl;
    this->inventory.printArmor();

    cout<<"Potions stored are: "<<endl;
    this->inventory.printPotions();
    
    cout<<"Spells are: "<<endl;
    this->inventory.printSpells();

}

void Hero::equipWeapon(string weaponName, string hand){
    if(hand != "Left" && hand != "Right" && hand != "Both"){
        cout<<"Hand must be Left or Right or Both"<<endl;
        return;
    }

    Weapon* temp= this->inventory.discardWeapon(weaponName);

    if(temp==NULL){
        cout<<"Weapon: "<<weaponName<<" wasnt found on your inventory"<<endl;
        return;
    }
    
    //Aν ειναι 2 handed weapon, κανω unequip και τα δυο weapon

    if(temp->isOneHandWeapon() == false){
        //το rightHand και leftHand δειχνουν στο ιδιο οπλο, αφου το οπλο ειναι twohand weapon
        //Eπομένως αρκει να το αφαιρεσω απο το ενα χερι.
        //Η unequipRightWeapon/unequipLeftWeapon κανει ελεγχο αν το οπλο που θα γινει unquip ειναι twoHandedWeapon
        //Επομένως αν ειναι το κανει unequip και απο τα δυο χερια μονη της.
        Weapon* t=this->equipment.unequipRightWeapon();
        if(t!=NULL)
            this->inventory.store(*t);
        
        this->equipment.add(*temp, "Both");
        cout<<"Weapon: "<<temp->getName()<<" equipped"<<endl;
        return;
    
    }else if(temp->isOneHandWeapon() == true && hand == "Right"){
        Weapon* t=this->equipment.unequipRightWeapon();
        if(t!=NULL)
            this->inventory.store(*t);
        this->equipment.add(*temp, "Right");
        cout<<"Weapon: "<<temp->getName()<<" equipped"<<endl;
        return;
    //Aν δωθει για onehand weapon, η επιλογη Both, το οπλο θα μπει by default στο αριστερο χερι
    }else if((temp->isOneHandWeapon() == true && hand == "Left") || (temp->isOneHandWeapon() == true && hand == "Both")){
        Weapon* t=this->equipment.unequipLeftWeapon();
        if(t!=NULL)
            this->inventory.store(*t);
        this->equipment.add(*temp, "Left");
        cout<<"Weapon: "<<temp->getName()<<" equipped"<<endl;
        return;
    }
}

//Kανει unequip ενα weapon και το βαζει στο inventory
void Hero::unequipWeapon(string hand){
    if(hand != "Left" && hand != "Right"){
        cout<<"Hand must be Left or Right"<<endl;
        return;
    }
    if(hand == "Left"){
        Weapon* tempWeapon = this->equipment.unequipLeftWeapon();
        if(tempWeapon==NULL){
            cout<<"You don't have equipped weapon to your left hand"<<endl;
            return;
        }
        this->addToInventory(*tempWeapon);
        return;
    }
    else if(hand == "Right"){
        Weapon* tempWeapon = this->equipment.unequipRightWeapon();
        if(tempWeapon==NULL){
            cout<<"You don't have equipped weapon to your Right hand"<<endl;
            return;
        }
        this->addToInventory(*tempWeapon);
        return;
    }
    else if(hand == "Both"){
        //Αφου το κρατανε και τα δυο χερια, δεν εχει σημασια, απο ποιο χερι θα κανω get
        Weapon* tempWeapon = this->equipment.getLeftWeapon();
        if(tempWeapon==NULL){
            cout<<"KATI THA BRO NA BALLO"<<endl;
            return;
        }
        if(tempWeapon->isOneHandWeapon()==false){
            cout<<"This weapon is onehand weapon. Please enter Right or Left"<<endl;
            return;
        }
        //Θα το αφαιρεσει και απο τα δυο χερια ετσι και αλλιως
        tempWeapon = this->equipment.unequipLeftWeapon();
        this->addToInventory(*tempWeapon);
        return;

    }

}

Weapon* Hero::getEquippedWeapon(string hand){
     if(hand != "Left" && hand != "Right"){
        cout<<"Hand must be Left or Right"<<endl;
        return NULL;
    }

    //Aν ζητηθει το equipped weapon απο το αριστερο χερι.
     if(hand == "Left")
        return this->equipment.getLeftWeapon();
    
    //Aν ζητηθει το equipped weapon απο το δεξι χερι.
    else if(hand == "Right")
        return this->equipment.getRightWeapon();

    return NULL;
}

Armor* Hero::getEquippedArmor(){
    return this->equipment.unequipArmor();
}


void Hero::equipArmor(string armor){

    Armor* temp= this->inventory.discardArmor(armor);
    if(temp==NULL){
        cout<<"Armor: "<<armor<<" wasnt found on your inventory"<<endl;
        return;
    }
    
    //το item που γινεται unequip, προστιθεται στο inventory
    Armor* t=this->equipment.unequipArmor();
    if(t!=NULL)
        this->inventory.store(*t);   
    this->equipment.add(*temp);
    cout<<"Armor: "<<temp->getName()<<" equipped"<<endl;
}

void Hero::unequipArmor(){
    Armor* tempArmor = this->equipment.unequipArmor();
    if(tempArmor == NULL){
        cout<< "You dont have armor equipped"<<endl;
        return;
    }
    this->addToInventory(*tempArmor);
}


void Hero::use(Potion& pot){

    //Aν το pottion εχει χρησιμοποιηθει
    if(pot.getUsed()){
        cout<<"This pottion is empty"<<endl;
        return;
    }
        

    int agil=0, dex=0, str=0;
    pot.get_attributes(str,dex,agil);

    //Αυξανει τα stats του ηρωα
    this->agility+=agil;
    this->strength+=str;
    this->dexterity+=dex;
    pot.usePotion();
}

Monster* get_random_monster(int level){
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static int monster_counter = 0;
    static std::uniform_int_distribution<int> monster_dist(1,4);
    
    int rand_result = monster_dist(rd);

    switch(rand_result){
        case 1:
            return new Monster("Monster_"+to_string(++monster_counter), level);
        case 2:
            return new Dragon("Dragon_"+to_string(++monster_counter), level);
        case 3:
            return new Exosceleton("Exosceleton_"+to_string(++monster_counter), level);
        case 4:
            return new Spirit("Spirit_"+to_string(++monster_counter), level);
    }
    
    return NULL;
}

int Monster::getAttackDamage(){
    if(damageLimiterRounds <= 0){
        damageLimiterRounds = 0;
        return this->attackDamage;
    }
    else{
        --damageLimiterRounds;
        return (((float) attackDamage)*((float) damageLimiterPercent))/100.0;
    }
}

bool Monster::receiveAttack(int damage){
    if(aaLimiterRounds <= 0){
        aaLimiterRounds = 0;
        if(avoid_attack_prob(avoidAttackProbability)){
            return 0;
        }
        else{
            this->reduceHealth(damage);
            return 1;
        }
    }
    else{
        --aaLimiterRounds;
        if(avoid_attack_prob(avoidAttackProbability-r_aaProbability)){
            return 0;
        }
        else{
            this->reduceHealth(damage);
            return 1;
        }
    }
}

Monster::Monster(string name, int level):
    Living(name, level),
    damageLimiterPercent(0),
    damageLimiterRounds(0),
    r_aaProbability(0),
    aaLimiterRounds(0),
    attackDamage(10),
    avoidAttackProbability(10)
    {

    };

Dragon::Dragon(string name, int level):
    Monster(name, level)
    {
        attackDamage += (level - 1)*3;
    }

Exosceleton::Exosceleton(string name, int level):
    Monster(name, level)
    {
        increaseHealth(level*25);
    }

Spirit::Spirit(string name, int level):
    Monster(name, level)
    {
        avoidAttackProbability += level*4;
        if(avoidAttackProbability > 60){
            avoidAttackProbability = 60;
        }
    }