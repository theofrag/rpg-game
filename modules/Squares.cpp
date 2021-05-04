#include "Squares.h"


Weapon* Market::discardWeapon(string weaponName){
    int i=0;
    for(vector<Weapon*>::iterator it=this->weapons.begin(); it!=this->weapons.end();++it){
        if(this->weapons.at(i)->getName()==weaponName){
            Weapon* temp=this->weapons.at(i);
            this->weapons.erase(it);
            return temp;
        }
        i++;
    }
    return NULL;


}

Armor* Market::discardArmor(string armorName){
    int i=0;
    for(vector<Armor*>::iterator it=this->armors.begin(); it!=this->armors.end();++it){
        if(this->armors.at(i)->getName()==armorName){
            Armor* temp=this->armors.at(i);
            this->armors.erase(it);
            return temp;
        }
        i++;
    }
    return NULL;


}

Potion* Market::discardPotion(string potionName){
    int i=0;
    for(vector<Potion*>::iterator it=this->potions.begin(); it!=this->potions.end();++it){
        if(this->potions.at(i)->getName()==potionName){
            Potion* temp=this->potions.at(i);
            this->potions.erase(it);
            return temp;
        }
        i++;
    }
    return NULL;
}

Spell* Market::discardSpell(string spellName){
    int i=0;
    for(vector<Spell*>::iterator it=this->spells.begin(); it!=this->spells.end();++it){
        if(this->spells.at(i)->getName()==spellName){
            Spell* temp=this->spells.at(i);
            this->spells.erase(it);
            return temp;
        }
        i++;
    }
    return NULL;
}



//Οι παρακατω προσθετουν ενα items στο market
void Market::add(Weapon& weapon ){
    this->weapons.push_back(&weapon);
}

void Market::add(Armor& armor ){
    this->armors.push_back(&armor);
}

void Market::add(Potion& potion ){
    this->potions.push_back(&potion);
}

void Market::add(Spell& spell ){
    this->spells.push_back(&spell);
}


void Market::print(){
    cout<<"--------------------MARKET MENU-----------------------"<<endl;
    cout<<"*****Weapons on market are: ********"<<endl;
    for(unsigned int i=0;i<this->weapons.size();i++){
        this->weapons.at(i)->printItem();
        cout<<"Price: "<<this->weapons.at(i)->getPrice()<<endl;        
        cout<<"__________________________________"<<endl;
    }
    cout<<"*****Armors on market : ********"<<endl;
    for(unsigned int i=0;i<this->armors.size();i++){
        this->armors.at(i)->printItem();
        cout<<"Price: "<<this->armors.at(i)->getPrice()<<endl; 
        cout<<"__________________________________"<<endl;
    }
    cout<<"*****Potions on market are: ********"<<endl;
    for(unsigned int i=0;i<this->potions.size();i++){
        this->potions.at(i)->printItem();
        cout<<"Price: "<<this->potions.at(i)->getPrice()<<endl; 
        cout<<"__________________________________"<<endl;
    }
    cout<<"*****Spells on market are: ********"<<endl;
    for(unsigned int i=0;i<this->spells.size();i++){
        this->spells.at(i)->printSpell();
        cout<<"Price: "<<this->spells.at(i)->getPrice()<<endl; 
        cout<<"__________________________________"<<endl;
    }


    cout<<"-------------------END OF MENU---------------------"<<endl;
}

Market::~Market(){
    for(unsigned int i=0;i<this->weapons.size();i++)
        delete (this->weapons.at(i));
    for(unsigned int i=0;i<this->armors.size();i++)
        delete (this->armors.at(i));
    for(unsigned int i=0;i<this->potions.size();i++)
        delete (this->potions.at(i));
    for(unsigned int i=0;i<this->spells.size();i++)
        delete (this->spells.at(i));
}