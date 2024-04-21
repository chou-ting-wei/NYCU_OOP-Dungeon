#include "../include/Monster.h"
#include "../include/General.h"
#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"

Monster::Monster(): GameCharacter("", "Monster", 0, 0, 0) {}

Monster::Monster(string name, int hp, int atk, int def):
    GameCharacter(name, "Monster", hp, atk, def) {}

int calculateDamage(int atk, int def){
    return atk * atk / (atk + def);
}

void Monster::printStatus(){
    cout << "Monster: " << getName() << endl;
    cout << "Health: " << getMaxHealth() << endl;
    cout << "Attack: " << getAttack() << endl;
    cout << "Defense: " << getDefense() << endl;
}

bool Monster::triggerEvent(Object* object){
    Player* player = dynamic_cast<Player*>(object);
    player -> triggerEvent(player);
    cout << "Player " << player -> getName() << ", you just encouter a monster." << endl;
    printStatus();
    char choice = '\0';
    int player_dmg = calculateDamage(player->getAttack(), getDefense());
    int monster_dmg = calculateDamage(getAttack(), player->getDefense());
    do {
        choice = tolower(choice);
        if(choice == 's'){
            clear();
            player -> triggerEvent(player);
        }
        else if(choice == 'r'){
            Room* tmp = player -> getCurrentRoom();
            player -> setCurrentRoom(player -> getPreviousRoom());
            player -> setPreviousRoom(tmp);
            clear();
            return true;
        }
        else if(choice == 'a') {
            clear();
            cout << "Player " << player -> getName() << " deals " << player_dmg
                << " damages to Monster " << getName() << endl;
            setCurrentHealth(getCurrentHealth()-player_dmg);
            if(getCurrentHealth() <= 0){
                cout << "Monster " << getName() << " has been killed." << endl; 
                player -> getCurrentRoom() -> popObject(this);
                return true;
            }
            cout << "Monster " << getName() << " deals " << monster_dmg
                << " damages to Player " << player -> getName() << endl;
            player -> setCurrentHealth(player->getCurrentHealth() - monster_dmg);
            if(player -> getCurrentHealth() <= 0){
                cout << REDB << "Player " << player -> getName() << " is dead." << NC << endl;
                return false;
            }
        } 
        cout << "(S)TATUS" << endl;
        cout << "(A)TTACK" << endl;
        cout << "(R)ETREAT" << endl;
        cout << "What do you want to do? > ";  
    } while(cin >> choice);
    
    return true;
}