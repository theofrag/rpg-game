#include "Grid.h"


int main(void){
    Grid grid("weapons.txt","armors.txt","potions.txt", "spells.txt");
    grid.displayMap();
    cout<<"\n\n\n\n"<<endl;
    string movement="null";

    cout<<"Controls\nUsage:\n[w] To move upwards\n[s] To move downwards\n[a] To move left\n[d] To move right\n"
        //<<"\n[b] To buy an item from a shop\n[z] To sell an item to a shop\n"
        <<"\n[e] To enter a shop"
        //<<"\n[q] To quit a market\n[c] To continue with initiating a transaction\n"
        <<"\n[1] To show statistics\n[2] To check your inventory\n[3] To equip an armor or a weapon\n"
        <<"[x] To exit the game"<<endl;
    
    while(1){
        getline(cin,movement);
        if(movement == "w"){
            grid.move("Up");
            grid.displayMap();
            cout<<"\n\n"<<endl;
        }else if(movement == "s"){
            grid.move("Down");
            grid.displayMap();
            cout<<"\n\n"<<endl;
        }else if(movement == "d"){
            grid.move("Right");
            grid.displayMap();
            cout<<"\n\n"<<endl;
        }else if(movement == "a"){
            grid.move("Left");
            grid.displayMap();
            cout<<"\n\n"<<endl;
        }else if(movement == "e"){
            grid.openMarketMenu();
            grid.displayMap();            
        }
        else if(movement=="1"){
            grid.displayStats();
        }else if(movement=="2"){
            string heroName;
            cout<<"Enter the name of your Hero"<<endl;
            getline(cin,heroName);
            grid.checkInventory(heroName);
        }else if(movement=="3"){
            string heroName;
            string itemName;
            string hand;
            string option;
            cout<<"Press:\n[1] To equip a weapon\n[2] To equip an armor"<<endl;
            // cin>>option;
            getline(cin,option);
            if(option == "1"){
                cout<<"Enter the name of your Hero: "<<endl;
                // cin>>heroName;
                getline(cin,heroName);
                cout<<"Enter item name: "<<endl;
                // cin>>itemName;
                getline(cin,itemName);
                cout<<"Select a hand: (input ignored if weapon is 2-handed)"<<endl;
                // cin>>hand;
                getline(cin,hand);
                grid.equip(heroName,itemName,hand);
            }
            else{
                cout<<"Enter the name of your Hero: "<<endl;
                // cin>>heroName;
                getline(cin,heroName);
                cout<<"Enter item name: "<<endl;
                // cin>>itemName;
                getline(cin,itemName);
                grid.equip(heroName,itemName);
            }
                
        }else if(movement=="u"){
            string heroName;
            string userPotion;
            cout<<"Enter the name of your Hero: "<<endl;
            getline(cin,heroName);
            cout<<"Enter potion name: "<<endl;
            getline(cin,userPotion);
            grid.use(heroName, userPotion);
        }
        else if(movement=="x"){
            grid.quitGame();
            break;
            
        }
        
    }
   
    return 0;
}
