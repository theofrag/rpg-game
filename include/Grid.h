#include "Squares.h"

class Grid{

private:
    NullSquare*** terrain;   //2d πινακας
    int height,width;
    int m,n; //Η θεση των ηρωων μια δεδομενη χρονικη στιμη, το κραταω εδω για να εχω αμεση προσβαση
    Hero* heroes[3];    //δεικτης σε 3 ηρωες
    int heroesCount;
    Monster** monsters;

    void printBattleMenu(){
        cout << "Battle Menu" << endl
            << "Pick an option: \n"
            << "[1] Normal attack\n"
            << "[2] Attack by casting a spell\n"
            << "[3] Use a potion\n"
            << "[4] Equip a weapon\n"
            << "[5] Equip an armor\n"
            << "[6] Display stats\n"
            << endl;
    }

    bool castSpell(Hero* hero, Monster* monster, Spell* sp);
    bool attack(Hero* hero, Monster* monster);
    void battle();

    //στο name μπαινει το ονομα του ηρωα που θα αγορασει, στο itemName
    //το ονομα του αντικειμενου που θα αγορασει
    void buy(string HeroName, string ItemName); 
    void sell(string HeroName, string ItemName);


public:
    Grid(string weaponFile,string armorFile,string potionsFile, string spellsFile);
    ~Grid();
    void move(string direction);
    void displayMap();
    
    

    //Στο name μπαινει το ονομα του ηρωα, που θελουμε να δουμε το inventory του
    void checkInventory(string name);

    //Αν δεν δωθει "hand" κανει equip armor
    void equip(string playerName, string itemName, string hand ="NULL");

    void use(string playerName,string potionName);
    void openMarketMenu();
    void closeMarketMenu();

    //Αν δεν ειναι σε μαχη, ετκυπωνει τα στατιστικα των heroes μονο.
    //Αν ειναι σε μαχη εκτυπωνει και τα στατιστικα των τερατων.
    void displayStats();

    void quitGame(){
        cout<<"Exit game......"<<endl;
        
    }

    
};