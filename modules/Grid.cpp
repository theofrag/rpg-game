#include "Grid.h"
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <Randomness.h>


//Το dmg που θα κανει το one hand weapon θα ειναι απο [ONE_HAND_F, ONE_HAND_T]
const static int ONE_HAND_F=1;
const static int ONE_HAND_T=30;

//Το dmg που θα κανει το two hand weapon θα ειναι απο [TWO_HAND_F, TWO_HAND_T]
const static int TWO_HAND_F=10;
const static int TWO_HAND_T=40;

//To res του armor απο [RES_FROM,RES_TWO]
const static int RES_FROM = 4;
const static int RES_TO = 30; 

const static int POTION_MIN_FACTOR = 5;
const static int POTION_MAX_FACTOR = 20;
const static int POTION_PRICE_MULTIPLIER = 100;    //Αυξανει μονιμα τα stats, ειναι λογικο να ειναι ακριβο.

const static int SPELL_MIN_FACTOR = 110;
const static int SPELL_MAX_FACTOR = 300;
const static int SPELL_PRICE_DIVIDER = 2;

const static int FIRE_SPELL_DAMAGE_FACTOR = 20; // Μειώνει την άμυνα του τέρατος κατά 20% της υγείας του
const static int LIGHTNING_SPELL_DEX_LIMITER = 10; // Μειώνει την πιθανότητα αποφυγής επίθεσης του τέρατος κατά 20%


//Σταθερα για να αποφασιζεται η τιμη του οπλου
//Οσο ανεβαινει το price, τοσο αυξανει ο ρυθμος αυξησης της τιμης
const static int PRICE=40;

//Σταθερα για να αποφασιζεται το min level του οπλου
//Οσο ανεβαινει η τιμη της MIN_LEVEL_DIVIDER, τοσο πεφτει το minLevel
const static int MIN_LEVEL_DIVIDER = 200; 

//MAX ITEMS αν ειδος(δηλαδη spells,weapons,armors,potions) που χωραει το store
const static int MAX_ITEMS=9;



Grid::Grid(string weaponFile,string armorFile,string potionsFile, string spellsFile):
monsters(NULL)
{

    //Πινακες με ονοματα απο weapons, armors, potions
    vector <Weapon*> weapons; 
    vector <Armor*> armors;   
    vector <Potion*> potions; 
    vector <Spell*> spells;

    ifstream file;
    file.open(weaponFile);

    ifstream file2;
    file2.open(armorFile);
    
    ifstream file3;
    file3.open(potionsFile);

    ifstream file4;
    file4.open(spellsFile);

    
    if(file.is_open() && file2.is_open() && file3.is_open() && file4.is_open()){
        string line;
        //file με ονοματα οπλων
        while(getline(file,line)){  
            int i= getIntFromRange(0,1);
            //Για να αποφασιζει τυχαια αν θα φτιαξει oneHnadWeapon ή twoHandWeapon
            if(i){
                int weaponDamage=getIntFromRange(ONE_HAND_F,ONE_HAND_T);
                int weaponPrice=weaponDamage* PRICE;    //Aν το οπλο κανει dmg=1, τοτε θα κοστιζει 40
                int weaponMinLevel=weaponPrice/MIN_LEVEL_DIVIDER;
                weapons.push_back(new OneHandWeapon(line,weaponMinLevel,weaponPrice,weaponDamage));
            }else{
                int weaponDamage=getIntFromRange(TWO_HAND_F,TWO_HAND_T);
                int weaponPrice=weaponDamage* PRICE;    //Aν το οπλο κανει dmg=1, τοτε θα κοστιζει 40
                int weaponMinLevel=weaponPrice/MIN_LEVEL_DIVIDER;
                weapons.push_back(new TwoHandWeapon(line,weaponMinLevel,weaponPrice,weaponDamage));
            }
        }
        //file με ονοματα απο armors
        while(getline(file2,line)){
            int armorResistance=getIntFromRange(RES_FROM,RES_TO);
                int armorPrice=armorResistance * PRICE;
                int armorMinLevel=armorPrice/MIN_LEVEL_DIVIDER;
            armors.push_back(new Armor(line,armorMinLevel,armorPrice,armorResistance));
        }
        //file με ονοματα απο potions.
        while(getline(file3,line)){
            //Ανολογα μα τον τυχαιο αριθμο, φτιαχνω τον αντιστοιχο τυπο potion
            int i=getIntFromRange(1,3);
            int potionStrength = getIntFromRange(POTION_MIN_FACTOR,POTION_MAX_FACTOR);
                int price = potionStrength * POTION_PRICE_MULTIPLIER;
                int minLevel = price / MIN_LEVEL_DIVIDER;
            if(i==1)
                potions.push_back(new StrenghtPotion(line, minLevel, price, potionStrength));
            else if(i==2)
                potions.push_back(new DexterityPotion(line, minLevel, price, potionStrength));
            else
                potions.push_back(new AgilityPotion(line, minLevel, price, potionStrength));
        
        }

        while(getline(file4,line)){
            int i = getIntFromRange(1,3);
            int spellDamageFactor = getIntFromRange(SPELL_MIN_FACTOR, SPELL_MAX_FACTOR);
            int spellReqMagicPower = getIntFromRange(SPELL_MIN_FACTOR/4, SPELL_MAX_FACTOR/4);
            int price = spellDamageFactor / SPELL_PRICE_DIVIDER;
            int minLevel = price / MIN_LEVEL_DIVIDER;
            if(i == 1){
                int monsterDamageLimiter = getIntFromRange(20, 40);
                spells.push_back(new IceSpell(line, price, minLevel, spellDamageFactor, spellReqMagicPower, monsterDamageLimiter));
            }
            else if(i==2){
                spells.push_back(new FireSpell(line, price, minLevel, spellDamageFactor, spellReqMagicPower, FIRE_SPELL_DAMAGE_FACTOR));
            }
            else{
                spells.push_back(new LightningSpell(line, price, minLevel, spellDamageFactor, spellReqMagicPower, LIGHTNING_SPELL_DEX_LIMITER));
            }
        
        }
        
        //κλεισιμο οσων αρχειων ανοιξαν
        file.close();
        file2.close();
        file3.close();
        file4.close();
    }

    //Αρχικοποιση των pointers με NULL
    for(int i=0;i<3;i++)
        heroes[i]=NULL;    

    
    cout<<"Pick a number of heroes: (1 to 3)"<<endl;
    // To t ειναι ενας int που δειχνει των αριθμο των ηρωων που επελεξε ο χρηστης
    int t;
    cin>>t;
    heroesCount = t;
    //Αν ο χρηστης επελεξε για αριθμο ηρωων αριθμο μεγαλυτερο του 3 ή αριθμο μικροτερο ή ισο του μηδενος,
    // θα φτιαχτει ενας ηρωας
    if(t>3 || t<=0) t=1;
    for(int i=0;i<t;i++){
        string playersName;
        int heroType;
        cout<<"Select your hero type:\n"
        <<"[1] Warrior\n"
        <<"[2] Paladin\n"
        <<"[3] Sorcerer\n"
        <<"[4] Undefined type of hero"<<endl;
        cin>>heroType;
        cout<<"Type a name for your hero: ";
        cin>>playersName;
        cout<<"\nYour hero name is "<<playersName<<endl;
        if(heroType==1)
            heroes[i]= new Warrior(playersName);
        else if(heroType==2)
            heroes[i] = new Paladin(playersName);
        else if(heroType==3)
            heroes[i] = new Sorcerer(playersName);
        else
            heroes[i] = new Hero(playersName);
    }


    //Δημιουργια terrain
    cout<<"\nTerrain creation\n"
        << "Enter your terrain's height:\n"
        << "Accepted values: 25 to 50" << endl;
    cin >> this->height;
    cout << "Enter your terrain's width:\n"
        << "Accepted values: 25 to 50" << endl;
    cin >> this->width;
    cout << endl;

    //Eλεγχω αν ο χρηστης εδωσε σωστα ορια
    if(this->height > 50) this->height=50;
    if(this->height < 25) this->height=25;
    if(this->width > 50) this->width=50;
    if(this->width < 25) this->width=25;


    this->terrain= new NullSquare** [this->height];
    for(int i=0;i<height;i++)
        this->terrain[i]=new NullSquare*[this->width];

    //Tα αρχικοποιω ολα με null στην αρχη  
    for(int i=0;i<this->height;i++){
        for(int j=0;j<this->width;j++)
            terrain[i][j] = NULL;
    }

    //!Τα ορια του tairrain ειναι παντα NonAccessivble
    for(int i=0;i<this->width;i++){
        this->terrain[0][i]=new NonAccessible();
        this->terrain[height-1][i]= new NonAccessible();
    }
    for(int i=1;i<this->height-1;i++){
        this->terrain[i][0]= new NonAccessible();
        this->terrain[i][width-1]= new NonAccessible();
    }
    
    int numberOfMarkets;
    cout << "Pick a number of shops:\nAccepted values: 0 to 20" << endl;

    cin>>numberOfMarkets;
    if(numberOfMarkets>20) numberOfMarkets = 20;

    //Εδω αρχιζει η δημιουργια των markets. Οι θεσεις που θα μπουν επιλεγονται τυχαια
    for(int i=0;i<numberOfMarkets;i++){
        int randomRow, randomColumn,randomNumberOfItems;
        randomRow = getIntFromRange(0,this->height-1);
        randomColumn = getIntFromRange(0,this->width-1);
        
        //Aν στην θεση που υποδεικνύεται υπαρχει ηδη καποιος τυπος square(nonAccessible ή market), επιλέγουμε νεα θεση
        while(this->terrain[randomRow][randomColumn]!=NULL){
            randomRow = getIntFromRange(0,this->height-1);
            randomColumn = getIntFromRange(0,this->width-1);
        }
        this->terrain[randomRow][randomColumn] = new Market(); 

        //Επιλέγεται τυχαιος αριθμος απο πλήθος weapons/armors/potions/spells
        randomNumberOfItems= getIntFromRange(0,MAX_ITEMS);

        int counter=0;
        
        //Η for δεν εχει update statement. Αυτο γιατι καθε φορα που γινεται erase
        //ενα στοιχειο, το it μειωνεται ετσι και αλλιως
        //Για τον ιδιο λογο, διαλεγω καθε φορα το στοιχειο 0

        for(vector<Weapon*>::iterator it=weapons.begin(); it != weapons.end() ; ){

            //Oταν ο counter φτασει την τιμη randomNumberOfItems, πρεπει να σταματησει η επαναληψη της for,
            //διοτι εχουν μπει οσα items θελουμε απο το συγκεκριμενο ειδος, μεσα στο market
            if(counter==randomNumberOfItems)
                break;
            Weapon* tempWeapon=weapons.front();
            weapons.erase(it);
            this->terrain[randomRow][randomColumn]->add(*tempWeapon);
            counter++;
        }
        counter=0;

        randomNumberOfItems= getIntFromRange(0,MAX_ITEMS);
        for(vector<Armor*>::iterator it=armors.begin(); it!=armors.end();   ){
            if(counter==randomNumberOfItems)
                break;
            Armor* tempArmor=armors.front();
            armors.erase(it);
            this->terrain[randomRow][randomColumn]->add(*tempArmor);
            counter++;
        }
        counter=0;
        randomNumberOfItems= getIntFromRange(0,MAX_ITEMS);
        for(vector<Potion*>::iterator it=potions.begin(); it!=potions.end();   ){
            if(counter==randomNumberOfItems)
                break;
            Potion* tempPotion=potions.front();
            potions.erase(it);
            this->terrain[randomRow][randomColumn]->add(*tempPotion);
            counter++;
        }
        

        randomNumberOfItems= getIntFromRange(0,MAX_ITEMS);
        for(int i = 0; i < randomNumberOfItems; ++i){
            if(spells.empty())
                break;
            this->terrain[randomRow][randomColumn]->add(*spells.front());
            spells.erase(spells.begin());
        }

    }


    for(int i=1;i<this->height-1;i++){
        for(int j=1;j<this->width-1;j++){
            if(this->terrain[i][j]==NULL)
                terrain[i][j]=new Common();
        }
            
    }


    m=height-2;
    n=width-2;
    terrain[m][n]->addHeroes(heroes);

    monsters = new Monster*[3];

    for(int i = 0; i < 3; ++i){
        monsters[i] = NULL;
    }
    

    //Διαγραφω οτι απεμεινε για να μην υπαρχουν leaks
    for(unsigned int i=0;i<weapons.size();i++)
        delete (weapons.at(i));
    for(unsigned int i=0;i<armors.size();i++)
        delete (armors.at(i));
    for(unsigned int i=0;i<potions.size();i++)
        delete (potions.at(i));
    for(unsigned int i=0;i<spells.size();i++)
        delete (spells.at(i));

}


// "up to go up, down to go down, left to go left, right to go right"
void Grid::move(string direction){    
    if(direction=="Up"){
        if(terrain[m-1][n]->get_id()==-1 ){
            cout<<"Non-accessible square"<<endl;
            return;
        }  
        this->m=this->m-1;
        terrain[m][n]->addHeroes(heroes);
        terrain[m+1][n]->removeHeroes();
    }else if(direction=="Down"){
        if(terrain[m+1][n]->get_id()==-1 ){
            cout<<"Non-accessible square"<<endl;
            return;
        }  
        m=m+1;
        terrain[m][n]->addHeroes(heroes);
        terrain[m-1][n]->removeHeroes();
    }else if(direction=="Left"){
        if(terrain[m][n-1]->get_id()==-1 ){
            cout<<"Non-accessible square"<<endl;
            return;
        }  
        n=n-1;
        terrain[m][n]->addHeroes(heroes);
        terrain[m][n+1]->removeHeroes();
    }else{
        if(terrain[m][n+1]->get_id()==-1 ){
            cout<<"Non-accessible square"<<endl;
            return;
        }  
        n=n+1;
        terrain[m][n]->addHeroes(heroes);
        terrain[m][n-1]->removeHeroes();
    }

    //Aν ειναι σε common square (id=0)
    if(terrain[m][n]->get_id() == 0 && decide_battle()){
        battle();
    }

}

void Grid::displayMap(){

    for(int i=0;i<this->height;i++){
        for(int j=0;j<this->width;j++){
            if(i==m && j==n){
                cout<<"o ";
                continue;
            }
            if(terrain[i][j]->get_id()==0){
                cout<<"- ";}
            else if(terrain[i][j]->get_id()==-1)
                cout<<"X ";
            else
                cout<<"$ ";
        }
            cout<<endl;
    }
}


void Grid::buy(string HeroName,string ItemName){

    if(this->terrain[this->m][this->n]->hasMarket()==false){ //Αν το τετραγωνακι ειναι common/nonAccesible
        cout<<"There is no market here"<<endl;

        return;
    }

    
    Hero* tempHero=NULL;
     
     //Ψαχνω σε ποιον ηρωα αντιστοιχει το συγκεκριμενο ονομα
    for(int i=0;i<3;i++){  
        if(this->heroes[i]==NULL)
            continue;
        if(this->heroes[i]->getName()== HeroName){
            tempHero=this->heroes[i];
            break;
        }
    }

    //Αν δεν υπαρχει ηρωας με τετοιο ονομα, επιστρεφει η συναρτηση
    if(tempHero==NULL){     
        cout<<"There is no Hero with that name"<<endl;
        return;
    }

    

    Weapon* temp1;
    Armor* temp2;
    Potion* temp3;
    Spell* temp4;

    //Αφαιρει το οπλο με ονομα ItemName απο το market
    //Aν δεν υπαρχει , επιστρεφει η συναρτηση 
    temp1 = this->terrain[this->m][this->n]->discardWeapon(ItemName);
    if(temp1 != NULL){

        //Αν δεν υπαρχουν τα χρηματα
        if(tempHero->getMoney()<temp1->getPrice()){
            this->terrain[this->m][this->n]->add(*temp1);
            cout<<"You dont have enough money, to buy this item"<<endl;
            return;
        }

        //Αν ο παικτης δεν ειναι στο καταλληλο level για να παρει το οπλο
        if(tempHero->getLevel()<temp1->get_minLevel()){
            this->terrain[this->m][this->n]->add(*temp1);
            cout<<"You need to level up, to buy this item"<<endl;
            return;
        }
        //Βαζω το οπλο στο inventory και μειωνω τα χρηματα του hero
        tempHero->addToInventory(*temp1);
        tempHero->reduceMoney(temp1->getPrice());
        return;
    }


    temp2 = this->terrain[this->m][this->n]->discardArmor(ItemName);

    if(temp2 != NULL){
        if(tempHero->getMoney()< temp2->getPrice()){
            this->terrain[this->m][this->n]->add(*temp2);
            cout<<"You dont have enough money, to buy this item"<<endl;
            return;
        }
        if(tempHero->getLevel()<temp2->get_minLevel()){
            this->terrain[this->m][this->n]->add(*temp2);
            cout<<"You need to level up, to buy this item"<<endl;
            return;
        }
        tempHero->addToInventory(*temp2);
        tempHero->reduceMoney(temp2->getPrice());
        return;
    }

    
    temp3 = this->terrain[this->m][this->n]->discardPotion(ItemName);
    if(temp3 != NULL){
        if(tempHero->getMoney()<temp3->getPrice()){
            this->terrain[this->m][this->n]->add(*temp3);
            cout<<"You dont have enough money, to buy this item"<<endl;
            return;
        }
        if(tempHero->getLevel()<temp3->get_minLevel()){
            this->terrain[this->m][this->n]->add(*temp3);
            cout<<"You need to level up, to buy this item"<<endl;
            return;
        }
        tempHero->addToInventory(*temp3);
        tempHero->reduceMoney(temp3->getPrice());
        return;
    }

    temp4 = this->terrain[this->m][this->n]->discardSpell(ItemName);
    if(temp4 != NULL){
        if(tempHero->getMoney()<temp4->getPrice()){
            this->terrain[this->m][this->n]->add(*temp4);
            cout<<"You dont have enough money, to buy this spell"<<endl;
            return;
        }
        if(tempHero->getLevel()<temp4->get_minLevel()){
            this->terrain[this->m][this->n]->add(*temp4);
            cout<<"You need to level up, to buy this spell"<<endl;
            return;
        }
        tempHero->addToInventory(*temp4);
        tempHero->reduceMoney(temp4->getPrice());
        return;
    }



//Σε περιπτωση που φτασουμε εδω, δεν εχει βρεθει το weapon στο market   
    cout<<"The Item wasn't found on the market"<<endl;
    return;
}


void Grid::sell(string HeroName, string ItemName){

    if(this->terrain[this->m][this->n]->hasMarket()==false){ //Αν το τετραγωνακι ειναι common/nonAccesible
        cout<<"There is no market here"<<endl;
        return;
    }
    
    Hero* tempHero=NULL;

    //Ψαχνω σε ποιον ηρωα αντιστοιχει το συγκεκριμενο ονομα
    for(int i=0;i<3;i++){   
        if(this->heroes[i]==NULL)
            continue;
        if(this->heroes[i]->getName()== HeroName){
            tempHero=this->heroes[i];
            break;
        }
    }

    //Αν δεν υπαρχει ηρωας με τετοιο ονομα, επιστρεφει η συναρτηση
    if(tempHero==NULL){     
        cout<<"There is no Hero with that name"<<endl;
        return;
    }

    //Πρωτα ψαχνω αν ο χρηστης προσπαθει να πουλησει οπλο που ειναι ηδη equipped
    //Αν συμβαινει αυτο, απλα κανει unequip το weapon/armor και το βαζει στο inventory πρώτα.

    Weapon* temp1 = tempHero->getEquippedWeapon("Left");
    if(temp1!=NULL && temp1->getName() == ItemName)
        tempHero->unequipWeapon("Left");
    
    temp1 = tempHero->getEquippedWeapon("Right");
    if(temp1!=NULL && temp1->getName() == ItemName)
        tempHero->unequipWeapon("Right");


    //Ψαχνω τωρα το οπλο που ειναι προς πωληση στο inventory
    //Aν ηταν οπλο/armor που ηταν equipped, τοτε θα εχει γινει unequip και θα εχει μπει στο inventory, στα παραπάνω βήματα

    temp1= tempHero->removeWeaponFromInventory(ItemName);
    if(temp1 != NULL){
        this->terrain[this->m][this->n]->add(*temp1);
        tempHero->increaseMoney(temp1->getPrice()/2);
        cout<<"You sold Weapon: "<<ItemName<<" for "<<temp1->getPrice()/2<<" gold"<<endl;
        return;
    }

    Armor* temp2= tempHero->getEquippedArmor();
    if(temp2!=NULL && temp2->getName() == ItemName)
        tempHero->unequipArmor();


    temp2= tempHero->removeArmorFromInventory(ItemName);
    if(temp2 != NULL){
        this->terrain[this->m][this->n]->add(*temp2);
        tempHero->increaseMoney(temp2->getPrice()/2);
        cout<<"You sold Armor: "<<ItemName<<" for "<<temp2->getPrice()/2<<" gold"<<endl;
        return;
    }
    Potion* temp3= tempHero->removePotionFromInventory(ItemName);
    if(temp3 != NULL){
        this->terrain[this->m][this->n]->add(*temp3);
        tempHero->increaseMoney(temp3->getPrice()/2);
        cout<<"You sold Potion: "<<ItemName<<" for "<<temp3->getPrice()/2<<" gold"<<endl;
        return;
    }

    Spell* temp4= tempHero->removeSpellFromInventory(ItemName);
    if(temp4 != NULL){
        this->terrain[this->m][this->n]->add(*temp4);
        tempHero->increaseMoney(temp4->getPrice()/2);
        cout<<"You sold Spell: "<<ItemName<<" for "<<temp4->getPrice()/2<<" gold"<<endl;
        return;
    }

    //Σε περιπτωση που φτασουμε εδω, δεν εχει βρεθει το weapon στο market   
    cout<<"You dont have this item and so you cannot sell it"<<endl;
    return;

}


void Grid::checkInventory(string name){

     Hero* tempHero=NULL;
    for(int i=0;i<3;i++){   //Ψαχνω σε ποιον ηρωα αντιστοιχει το συγκεκριμενο ονομα
        if(this->heroes[i]==NULL)
            continue;
        if(this->heroes[i]->getName()== name){
            tempHero=this->heroes[i];
            break;
        }
    }
    if(tempHero==NULL){     //Αν δεν υπαρχει ηρωας με τετοιο ονομα, επιστρεφει η συναρτηση
        cout<<"There is no Hero with that name"<<endl;
        return;
    }

    //Κανει print , όλα τα items που υπαρχουν στο inventory
    tempHero->checkInventory();

}

//Κανει equip ενα weapon ή μια armor. 
//Αν δωθει ορισμα στο hand, θα ψαξει να κανει equip ενα weapon αλλιως θα κανει equip μια armor
void Grid::equip(string playerName, string itemName, string hand /*="NULL"*/){
     Hero* tempHero=NULL;
    for(int i=0;i<3;i++){   //Ψαχνω σε ποιον ηρωα αντιστοιχει το συγκεκριμενο ονομα
        if(this->heroes[i]==NULL)
            continue;
        if(this->heroes[i]->getName()== playerName){
            tempHero=this->heroes[i];
            break;
        }
    }

    //Αν δεν υπαρχει ηρωας με τετοιο ονομα, επιστρεφει η συναρτηση
    if(tempHero==NULL){     
        cout<<"There is no Hero with that name"<<endl;
        return;
    }

    if(hand == "NULL"){
        tempHero->equipArmor(itemName);}
    else
        tempHero->equipWeapon(itemName,hand);
}


void Grid::use(string playerName, string potionName){

     Hero* tempHero=NULL;
    for(int i=0;i<3;i++){   //Ψαχνω σε ποιον ηρωα αντιστοιχει το συγκεκριμενο ονομα
        if(this->heroes[i]==NULL)
            continue;
        if(this->heroes[i]->getName()== playerName){
            tempHero=this->heroes[i];
            break;
        }
    }
    if(tempHero==NULL){     //Αν δεν υπαρχει ηρωας με τετοιο ονομα, επιστρεφει η συναρτηση
        cout<<"There is no Hero with that name"<<endl;
        return;
    }
    Potion* tempPotion = tempHero->removePotionFromInventory(potionName);
    tempHero->use(*tempPotion); 
    delete tempPotion;

    return;
}

//Aν ο παικτης καλεσει αυτη την συναρτηση σημαινει οτι οι ηρωες του
//βρισκονται σε διαδικασια buy/sell.
//Πρεπει να καλεσει την closeMarketMenu για να βγουν απο αυτη την διαδικασια.
void Grid::openMarketMenu(){

    if(this->terrain[this->m][this->n]->hasMarket()==false){
        cout<<"No market here"<<endl;
        return;
    }

    //Κανει print τα items του market
    this->terrain[this->m][this->n]->print();
    string action;
    cout << "Usage:\n[s] Sell an item\n[b] Buy an item\n[q] Exit market\n" << endl;

    while(getline(cin,action)){
        if(action=="b"){
            string action;
            cout<<"Enter the name of your Hero and the name of the Item that you want to buy: "<<endl;
            string heroName,itemName;
            cout<<"Hero name: "<<endl;
            getline(cin,heroName);
            cout<<"Item name: "<<endl;
            getline(cin,itemName);
            this->buy(heroName,itemName);

        }else if(action=="s"){
            string action;

            cout<<"Enter the name of your Hero and the name of the Item that you want to sell: "<<endl;
            string heroName,itemName;
            cout<<"Hero name: "<<endl;
            getline(cin,heroName);
            cout<<"Item name: "<<endl;
            getline(cin,itemName);
            this->sell(heroName,itemName);

        }
        else if(action == "q"){
            cout<<"\n\n\n\n\n\n\n\n\n ----------------EXITED FROM MARKET--------------------"<<endl;  
            break;
        }
        else{
            cout<<"Invalid action.\n You must exit market first"<<endl;
        }

    }

    return;
}

void Grid::closeMarketMenu(){

    cout<<"\n\n\n\n\n\n\n\n\n ----------------EXITED FROM MARKET--------------------"<<endl;  
}


void Grid::displayStats(){
    for(int i=0;i<3;i++){
        if(this->heroes[i]!= NULL){
            cout<<"________________________________________\n"
            <<"Hero: "<<this->heroes[i]->getName()<<" statistics\n"
            <<"________________________________________\n"
            <<"\tLevel\t\t: "<<this->heroes[i]->getLevel()
            <<"\n\tExperience\t: "<<this->heroes[i]->getExperience()
            <<"\n\tHealth\t\t: "<<this->heroes[i]->getHealth()
            <<"\n\tStrength\t: "<<this->heroes[i]->getStrength()
            <<"\n\tDexterity\t: "<<this->heroes[i]->getDexterity()
            <<"\n\tAgility\t\t: "<<this->heroes[i]->getAgility()
            <<"\n\tMagic\t\t: "<<this->heroes[i]->getMagicPower()
            <<"\n\tMoney\t\t: "<<this->heroes[i]->getMoney()<<endl;
            cout<<"________________________________________"<<endl;
        }
    }

    for(int i=0;i<heroesCount;i++){

        int damageLimiterPercent, damageLimiterRounds, r_aaProbability;
        int aaLimiterRounds, attackDamage, avoidAttackProbability;
        
        if(this->monsters[i]!= NULL){
            monsters[i]->get_stats(damageLimiterPercent, damageLimiterRounds, r_aaProbability,
             aaLimiterRounds, attackDamage, avoidAttackProbability);
            
            cout<<"________________________________________\n"
            <<"Monster: "<<this->monsters[i]->getName()<<" statistics\n"
            <<"________________________________________\n"
            <<"\n\tHealth\t\t\t: "<<this->monsters[i]->getHealth()
            <<"\n\tLevel\t\t\t: "<<this->monsters[i]->getLevel()<<endl
            <<"\n\tNormal attack damage:\t"<<attackDamage;
            if(damageLimiterRounds > 0){
                cout << "\n\tCurrent attack damage:\t" << (((float) attackDamage)*((float) damageLimiterPercent))/100.0
                    << " (reduced because of IceSpell, valid for the next "
                    << damageLimiterRounds << " rounds)";
            }
            cout<<"\n\tNormal chance of avoiding an attack:\t"<<avoidAttackProbability<<"%"<<endl;
            if(aaLimiterRounds > 0){
                cout << "\nCurrent chance of avoiding an attack:\t"
                << (avoidAttackProbability-r_aaProbability)/100.0<<"%"
                    << " (reduced because of LightningSpell, valid for the next "
                    << aaLimiterRounds << " rounds)" << endl;
            }
            cout<<"________________________________________"<<endl;
        }
    }
}


Grid::~Grid(){
    for(int i=0;i<this->height;i++){
        for(int j=0;j<this->width;j++){
            delete this->terrain[i][j];
        }
        delete [] this->terrain[i];
    }
    delete [] this->terrain;
    delete [] monsters;

    for(int i=0;i<this->heroesCount;i++){
        delete this->heroes[i];
    }

}

void Grid::battle(){

    vector<Hero*> aliveHeroes;
    vector<Monster*> aliveMonsters;

    for(int i = 0; i < heroesCount; ++i){
        monsters[i] = get_random_monster(heroes[0]->getLevel());
        aliveHeroes.push_back(heroes[i]);
        aliveMonsters.push_back(monsters[i]);
    }

    if(heroesCount != 1){
        cout << heroesCount << " monsters have appeared! Prepare for a battle!" << endl;
    }
    else{
        cout << "1 monster has appeared! Prepare for a battle!" << endl;
    }

    bool heroesTurn;
    string userInput;

    while(!aliveHeroes.empty() && !aliveMonsters.empty()){
        Hero* currentHero = aliveHeroes.front();
        Monster* currentMonster = aliveMonsters.front();
        cout << currentHero->getName() << " VS " << currentMonster->getName() << endl;
        heroesTurn = 1;

        while(1){

            if(heroesTurn){
                printBattleMenu();
                getline(cin, userInput);
            }
            else{
                currentMonster->increaseHealth(2);

                int damage = currentMonster->getAttackDamage();
                Armor* currentHeroArmor = currentHero->getEquippedArmor();
                if(currentHeroArmor != NULL){
                    float armorResistance = currentHeroArmor->getResistance();
                    damage = ((float) damage) * ((100.0 - armorResistance) * 0.01);
                }

                
                if(avoid_attack_prob(100-currentHero->getDexterity())){
                    currentHero->reduceHealth(damage);
                    cout << currentHero->getName() << " received "
                        << damage << " damage!" << endl;
                    cout << currentHero->getName() << " current health:\t"
                        << currentHero->getHealth() << endl;
                    if(currentHero->getHealth() <= 0){
                        cout << currentHero->getName() << " has been defeated!" << endl;
                        aliveHeroes.erase(aliveHeroes.begin());
                        break;
                    }
                }
                else{
                    cout << currentHero->getName() << " avoided the attack" << endl;
                }

                for(unsigned int i = 0; i < aliveHeroes.size(); ++i){
                    aliveHeroes.at(i)->increaseHealth(2);
                    aliveHeroes.at(i)->increaseMagicPower(5);
                    cout << aliveHeroes.at(i)->getName() << ":\t+2 Health\n"
                        << aliveHeroes.at(i)->getName() << ":\t+20 Magic Power" << endl;
                }
                for(unsigned int i = 0; i < aliveMonsters.size(); ++i){
                    aliveMonsters.at(i)->increaseHealth(2);
                    cout << aliveMonsters.at(i)->getName() << ":\t+2 Health" << endl;
                }
                heroesTurn = 1;
                continue;
            }
            
            if(userInput == "1"){
                // [1] Normal attack
                if(attack(currentHero, currentMonster)){
                    aliveMonsters.erase(aliveMonsters.begin());
                    for(int i = 0; i < heroesCount; ++i){
                        if(monsters[i] == currentMonster){
                            monsters[i] = NULL;
                        }
                    }
                    delete currentMonster;
                    break;
                }
                heroesTurn = 0;
            }
            else if(userInput == "2"){
                // [2] Attack by casting a spell
                string userSpell;

                cout << "Type the name of the spell that you want to cast." << endl;
                getline(cin, userSpell);
                Spell* sp = currentHero->get_spell(userSpell);
                if(sp == NULL){
                    cout << "Unknown spell" << endl;
                    continue;
                }
                if(currentHero->getMagicPower()<sp->get_reqMagicPower()){
                    cout << "Not enough magic power" << endl;
                    continue;
                }
                if(currentHero->getLevel()<sp->get_minLevel()){
                    cout << "You need to level up to use this spell" << endl;
                    continue;
                }
                if(castSpell(currentHero, currentMonster, sp)){
                    aliveMonsters.erase(aliveMonsters.begin());
                    for(int i = 0; i < heroesCount; ++i){
                        if(monsters[i] == currentMonster){
                            monsters[i] = NULL;
                        }
                    }
                    delete currentMonster;
                    break;
                }
                heroesTurn = 0;

            }
            else if(userInput == "3"){
                // [3] Use a potion
                string userPotion;

                cout << "Type the name of the potion that you want to use." << endl;
                getline(cin, userPotion);
                Potion* potion = currentHero->get_potion(userPotion);
                if(potion == NULL){
                    cout << "Unknown potion" << endl;
                    continue;
                }
                use(currentHero->getName(), userPotion);
                heroesTurn = 0;
            }
            else if(userInput == "4"){
                // [4] Equip a weapon
                cout << "Enter weapon name:" << endl;
                string weaponName, hand;
                getline(cin, weaponName);
                cout << "Enter the hand to which to equip the weapon: (Left/Right)" << endl;
                getline(cin, hand);
                currentHero->equipWeapon(weaponName, hand);
                heroesTurn = 0;
            }
            else if(userInput == "5"){
                // [5] Equip an armor
                cout << "Enter armor name:" << endl;
                string armor;
                getline(cin, armor);
                currentHero->equipArmor(armor);
                heroesTurn = 0;
            }
            else if(userInput == "6"){
                // [6] Display stats
                displayStats();
            }
        }
    }

    for(int i = 0; i < heroesCount; ++i){
        if(heroes[i]->getHealth() <= 0){
            heroes[i]->increaseHealth(heroes[i]->getHealth()*(-1) + 100 + (heroes[i]->getLevel()*25)/2);
        }
        if(monsters[i] != NULL){
            delete monsters[i];
            monsters[i] = NULL;
        }
    }

    if(!aliveHeroes.empty()){
        for(int i = 0; i < heroesCount; ++i){
            heroes[i]->increaseMoney(heroes[i]->getLevel()*heroesCount*10);
            cout << heroes[i]->getName() << ":\t+" << heroes[i]->getLevel()*heroesCount*10 << " Money" << endl;
            heroes[i]->increaseExperience(heroes[i]->getLevel()*heroesCount*100);
            heroes[i]->levelUp();
        }
    }
    else{
        for(int i = 0; i < heroesCount; ++i){
            heroes[i]->increaseMoney(heroes[i]->getLevel()*heroesCount);
            int moneyLost = heroes[i]->getMoney()/2;
            heroes[i]->reduceMoney(moneyLost);
            cout << heroes[i]->getName() << ":\t-" << moneyLost << " Money" << endl;
        }
    }
}

bool Grid::attack(Hero* hero, Monster* monster){
    
    int damage = hero->getStrength() + hero->getWeaponDamage();
    if(monster->receiveAttack(damage)){
        cout << monster->getName() << " received "
            << damage << " damage!" << endl;
        cout << monster->getName() << " current health:\t"
            << monster->getHealth() << endl;
        if(monster->getHealth() <= 0){
            cout << monster->getName() << " has been defeated!" << endl;
            return 1;
        }
    }
    else{
        cout << monster->getName() << " avoided the attack!" << endl;
    }
    return 0;
}

bool Grid::castSpell(Hero* hero, Monster* monster, Spell* sp){
    int sp_dmgLimiter, sp_defLimiter, sp_dexLimiter;
    sp->get_attributes(sp_dmgLimiter, sp_defLimiter, sp_dexLimiter);

    if(sp_dmgLimiter > 0){
        monster->enableDamageLimiter(sp_dmgLimiter, 2);
    }
    if(sp_defLimiter > 0){
        monster->reduceHealth(monster->getHealth()*sp_defLimiter/100);
    }
    if(sp_dexLimiter > 0){
        monster->reduceAAProbability(sp_dexLimiter, 3);
    }

    hero->reduceMagicPower(sp->get_reqMagicPower());

    int damage = (hero->getStrength() + hero->getDexterity() + hero->getWeaponDamage())*sp->get_damageFactor()/100;
    if(monster->receiveAttack(damage)){
        cout << monster->getName() << " received "
            << damage << " damage!" << endl;
        cout << monster->getName() << " current health:\t"
            << monster->getHealth() << endl;
        if(monster->getHealth() <= 0){
            cout << monster->getName() << " has been defeated!" << endl;
            return 1;
        }
    }
    else{
        cout << monster->getName() << " avoided the attack!" << endl;
    }
    return 0;
}