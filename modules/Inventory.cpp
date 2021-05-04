#include "Inventory.h"


void Inventory::store(Weapon& weapon){

    //Αν δεν χωρανε αλλα οπλα
    if(this->weapons.size() == this->maxWeapons ){
        cout<<"Cant store more Weapons"<<endl;
        return;    
    }

    //Προσθεσε το οπλο και εκτυπωσε καταλληλο μηνυμα.
    this->weapons.push_back(&weapon);
    cout<<"Weapon: "<<weapon.getName()<<" added to inventory"<<endl;
}


void Inventory::store(Armor& armor){

    //Αν δεν χωρανε αλλες armors
    if(this->armors.size() == this->maxArmors ){
        cout<<"Cant store more Armors"<<endl;
        return;   
    }

    //Προσθεσε την armor και εκτυπωσε καταλληλο μηνυμα
    this->armors.push_back(&armor);
    cout<<"Armor: "<<armor.getName()<<" added to inventory"<<endl;
}

void Inventory::store(Potion& potion){

    //Αν δεν χωρανε αλλα potions
    if(this->potions.size() == this->maxPotions ){
        cout<<"Cant store more Potions"<<endl;
        return;   
    }

    //Προσθεσε το potion και εκτυπωσε καταλληλο μηνυμα.
    this->potions.push_back(&potion);
    cout<<"Potion: "<<potion.getName()<<" added to inventory"<<endl;
}

void Inventory::store(Spell& spell){

    //Αν δεν χωρανε αλλα potions
    if(this->potions.size() == this->maxPotions ){
        cout<<"Cant store more Spells"<<endl;
        return;   
    }

    //Προσθεσε το spell και εκτυπωσε καταλληλο μηνυμα.
    this->spells.push_back(&spell);
    cout<<"Spell: "<<spell.getName()<<" added to inventory"<<endl;
}


Weapon* Inventory::discardWeapon(string name){

    int i=0;
    //Βρες το weapon με ονομα name και αφαιρεσε το απο τον inventory.
    //Σε περιπτωση που υπαρχουν δυο με το ιδιο ονομα, αφαιρει το πρωτο
    for(vector<Weapon*>::iterator it=this->weapons.begin(); it!=this->weapons.end();++it){
        if(this->weapons.at(i)->getName()==name){
            Weapon* temp=this->weapons.at(i);
            this->weapons.erase(it);
            return temp;
        }
        i++;
    }

    //Αν δεν τον βρεις, επεστρεψε NULL
    return NULL;
}

Weapon* Inventory::getWeapon(string name){
    
    for(unsigned int i=0; i<this->weapons.size();i++){
        if(this->weapons.at(i)->getName()==name)
            return this->weapons.at(i);
    }
    
    //Αν δεν βρεις το οπλο , επεστρεψε NULL
    return NULL;
}



Armor* Inventory::discardArmor(string name){
    int i=0;

    //Βρες την armor με ονομα name και αφαιρεσε την απο τον inventory. 
    //Σε περιπτωση που υπαρχουν δυο με το ιδιο ονομα, αφαιρει το πρωτο
    for(vector<Armor*>::iterator it=this->armors.begin(); it!=this->armors.end();++it){
        if(this->armors.at(i)->getName()==name){
            Armor* temp=this->armors.at(i);
            this->armors.erase(it);
            return temp;
        }
        i++;
    }

    //Αν δεν την βρεις
    return NULL;
}

Armor* Inventory::getArmor(string name){
    
    for(unsigned int i=0; i<this->armors.size();i++){
        if(this->armors.at(i)->getName()==name)
            return this->armors.at(i);
    }
    
    //Αν δεν βρεις την armor , επεστρεψε NULL
    return NULL;
}



Potion* Inventory::discardPotion(string name){

    int i=0;
    //Βρες το potion με ονομα name και αφαιρεσε το απο τον inventory. 
    //Σε περιπτωση που υπαρχουν δυο με το ιδιο ονομα, αφαιρει το πρωτο
    for(vector<Potion*>::iterator it=this->potions.begin(); it!=this->potions.end();++it){
        if(this->potions.at(i)->getName()==name){
            Potion* temp=this->potions.at(i);
            this->potions.erase(it);
            return temp;
        }
        i++;
    }

    //Αν δεν το βρεις
    return NULL;
}

Potion* Inventory::getPotion(string name){
    
    for(unsigned int i=0; i<this->potions.size();i++){
        if(this->potions.at(i)->getName()==name)
            return this->potions.at(i);
    }
    
    //Αν δεν βρεις το pottion , επεστρεψε NULL
    return NULL;
}


Spell* Inventory::discardSpell(string name){

    int i=0;
    //Βρες το spell με ονομα name και αφαιρεσε το απο τον inventory. 
    //Σε περιπτωση που υπαρχουν δυο με το ιδιο ονομα, αφαιρει το πρωτο
    for(vector<Spell*>::iterator it=this->spells.begin(); it!=this->spells.end();++it){
        if(this->spells.at(i)->getName()==name){
            Spell* temp=this->spells.at(i);
            this->spells.erase(it);
            return temp;
        }
        i++;
    }

    //Αν δεν το βρεις
    return NULL;
}

Spell* Inventory::getSpell(string name){
    
    for(unsigned int i=0; i<this->spells.size();i++){
        if(this->spells.at(i)->getName()==name)
            return this->spells.at(i);
    }
    
    //Αν δεν βρεις το spell , επεστρεψε NULL
    return NULL;
}


//print τα weapons του inventory
void Inventory::printWeapons(){
    for(unsigned int i=0;i<this->weapons.size();i++){
        this->weapons.at(i)->printItem();
        cout<<endl;
    }
}


//print τις armors του inventory
void Inventory::printArmor(){
    for(unsigned int i=0;i<this->armors.size();i++){
        this->armors.at(i)->printItem();
        cout<<endl;
    }
}

//print τα potions του inventory
void Inventory::printPotions(){
    for(unsigned int i=0;i<this->potions.size();i++){
        this->potions.at(i)->printItem();
        cout<<endl;
    }
}

void Inventory::printSpells(){
    for(unsigned int i=0;i<this->spells.size();i++){
        this->spells.at(i)->printSpell();
        cout<<endl;
    }
}

//print potions/armors/weapons που υπαρχουν στο inventory
void Inventory:: printInventory(){
    this->printWeapons();
    this->printArmor();
    this->printPotions();
    this->printSpells();
}


Inventory:: ~Inventory(){
    
    for(unsigned int i=0;i<this->weapons.size();i++)
        delete (this->weapons.at(i));
    for(unsigned int i=0;i<this->armors.size();i++)
        delete (this->armors.at(i));
    for(unsigned int i=0;i<this->potions.size();i++)
        delete (this->potions.at(i));
    for(unsigned int i=0;i<this->spells.size();i++)
        delete (this->spells.at(i));
    
}




//Κανε unequip το δεξι weapon και επεστρεψε δεικτη στο weapon αυτο
Weapon* Equipment::unequipRightWeapon(){

    //Αν δεν κρατουσε ετσι και αλλιως οπλο
    if(this->rightHand==NULL)
        return NULL;
    
    Weapon* temp= this->rightHand;

    //Αν κρατουσε το οπλο και με τα δυο χερια, βαλε null και στα δυο χερια
    if(temp->isOneHandWeapon()==false)
        this->leftHand=NULL;

    this->rightHand=NULL;
    return temp;
}


// Κανε unequip το αριστερο weapon και επεστρεψε δεικτη στο weapon αυτο
Weapon* Equipment::unequipLeftWeapon(){
    if(this->leftHand==NULL)
        return NULL;
    
    Weapon* temp= this->leftHand;
    if(temp->isOneHandWeapon()==false)
        this->rightHand=NULL;
    this->leftHand=NULL;
    return temp;
}

Armor* Equipment::unequipArmor(){
    if(this->armor == NULL)
        return NULL;

    Armor* temp= this->armor;
    return temp;
}

Weapon* Equipment::getRightWeapon(){
    return this->rightHand;
}

Weapon* Equipment::getLeftWeapon(){
    return this->leftHand;
}

Armor* Equipment:: getArmor(){
    return this->armor;
}


//Κανει equip μια armor
void Equipment::add(Armor& arm){
    this->armor=&arm;
}

void Equipment::add(Weapon& weap, string hand){
 
     if(hand != "Left" && hand !="Right" && hand !="Both"){
        hand="Right";        //default χερι
    }else if(weap.isOneHandWeapon()==false){
        this->rightHand=&weap;
        this->leftHand=&weap;
    
    }else if(hand=="Right" && weap.isOneHandWeapon()==true){
        this->rightHand=&weap;
    }else if(hand=="Left" && weap.isOneHandWeapon()==true){
        this->leftHand=&weap;
    }else{
        cout<<"Invalid option."<<endl;
    }
}


void Equipment::print(){
    cout<<"Your equipment: "<<endl;
    if(this->rightHand != NULL)
        this->rightHand->printItem();
    if(this->leftHand != NULL && this->leftHand != this->rightHand)
        this->leftHand->printItem();
    if(this->armor!=NULL)
        this->armor->printItem();
}

Equipment::~Equipment(){
    if(this->leftHand!=NULL)
        delete this->getLeftWeapon();
    if(this->rightHand!=NULL)
        delete this->getRightWeapon();
    if(this->armor !=NULL)
        delete this->getArmor();
}