#include "../include/Player.h"
#include "../include/General.h"
#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"

Player::Player(){}
Player::Player(string name, int hp, int atk, int def, int hun, int thr): GameCharacter(name, "Player", hp, atk, def), hunger(hun), thirst(thr) {}

void Player::addItem(Item new_item){
    string type = new_item.getType();
    if(type == "poison"){
        addPoison(new_item);
    } 
    else if(type == "food") {
        addFood(new_item);
    }
    else{
        inventory.push_back(new_item);
    }
}

void Player::increaseStates(int hp, int atk, int def){
    setCurrentHealth(min(getCurrentHealth() + hp, getMaxHealth()));
    setAttack(getAttack() + atk);
    setDefense(getDefense() + def);
}

void Player::changeRoom(Room* new_room){
    previousRoom = currentRoom;
    currentRoom = new_room;
}

bool Player::triggerEvent(Object*){
    cout << "------------------ STATUS ------------------" << endl;

    cout << getName() << endl;
    cout << "> Health: "  << getCurrentHealth() << "/" << getMaxHealth() << endl;
    cout << "> Attack: "  << getAttack() << endl;
    cout << "> Defense: " << getDefense() << endl;
    cout << "> Hunger: " << getHunger() << endl;
    cout << "> Thirst: " << getThirst() << endl;
    cout << "> Poison: " << endl;
    if(poison.size() != 0){
        for(Item i: poison){
            cout << "  - " << RED+i.getName()+NC << endl;
        }
    }
    else cout << "  (empty)" << endl;
    cout << "--------" << endl;

    auto inve = getInventory();
    sort(inve.begin(), inve.end(), [](Item a, Item b){ return a.getType() < b.getType(); });
    cout << "> Items: " << endl;
    if(inve.size() != 0){
        for(auto i: inve){
            cout << "  - " << CYN+i.getType()+NC << " " << i.getName() << endl;
        }
    }
    else cout << "  (empty)" << endl;

    cout << "--------" << endl;
    cout << "> Equipments: " << endl;
    cout << "  - Sword : " << (sword == nullptr ? "(empty)" : sword->getName()) << endl;
    cout << "  - Shield: " << (shield == nullptr ? "(empty)" : shield->getName()) << endl;

    cout << "--------" << endl;
    cout << "> Foods: " << endl;
    if(food.size() != 0){
        for(Item i: food){
            cout << "  - " << i.getName() << endl;
        }
    }
    else cout << "  (empty)" << endl;

    cout << "--------------------------------------------" << endl;
    return true;
}

void Player::setCurrentRoom(Room* room){
    currentRoom = room;
}

void Player::setPreviousRoom(Room* room){
    previousRoom = room;
}

void Player::setInventory(vector<Item> invent){
    inventory = invent;
}

Room* Player::getCurrentRoom(){
    return currentRoom;
}
Room* Player::getPreviousRoom(){
    return previousRoom;
}
vector<Item> Player::getInventory(){
    return inventory;
}

Item* Player::getSword(){
    return sword;
}

Item* Player::getShield(){
    return shield;
}

void Player::setSword(Item* newSword){
    increaseStates(newSword->getHealth(), newSword->getAttack(), newSword->getDefense());
    for(auto it=inventory.begin();it!=inventory.end();it++){
        if(it->getName() == newSword->getName()){
            inventory.erase(it);
            break;
        }
    }
    if(sword != nullptr){
        increaseStates(-sword->getHealth(), -sword->getAttack(), -sword->getDefense());
        inventory.push_back(*sword);
    }
    sword = newSword;
}

void Player::setShield(Item* newShield){
    increaseStates(newShield->getHealth(), newShield->getAttack(), newShield->getDefense());
    for(auto it=inventory.begin();it!=inventory.end();it++){
        if(it->getName() == newShield->getName()){
            inventory.erase(it);
            break;
        }
    }
    if(shield != nullptr){
        increaseStates(-shield->getHealth(), -shield->getAttack(), -shield->getDefense());
        inventory.push_back(*shield);
    }
    shield = newShield;
}

void Player::addFood(Item _food){
    this->food.push_back(_food);
}

void Player::addPoison(Item _poison){
    this->poison.push_back(_poison);
}

vector<Item> Player::getFood(){
    return food;
}

vector<Item> Player::getPoison(){
    return poison;
}

int Player::getHunger(){
    return hunger;
}

int Player::getThirst(){
    return thirst;
}

void Player::setHunger(int hun){
    this->hunger = hun;
}

void Player::setThirst(int thr){
    this->thirst = thr;
}

void Player::equip(){
    while(true){
        clear();
        cout << "> Equipment: " << endl;
        cout << "  - Sword : " << (sword == nullptr ? "(empty)" : (sword->getName()) + " Attack: " + to_string(sword->getAttack()) + " Defense: " + to_string(sword->getDefense())) << endl;
        cout << "  - Shield: " << (shield == nullptr ? "(empty)" : (shield->getName()) + " Attack: " + to_string(shield->getAttack()) + " Defense: " + to_string(shield->getDefense())) << endl;
        string str;
        do {
            transform(str.begin(), str.end(), str.begin(), [](unsigned char c) -> unsigned char { return std::tolower(c); });
            cout << "(SW)ord" << endl;
            cout << "(SH)ield" << endl;
            cout << "(E)xit" << endl;
            cout << "Which equipment do you want to put on? > ";
            if(str == "sw" || str == "sh" || str == "e") break;
        }while(cin >> str);
    
        if(str == "e") return;

        if(str == "sw"){
            clear();
            cout << "Sword: " << (sword == nullptr ? "(empty)" : (sword->getName()) + " Attack: " + to_string(sword->getAttack()) + " Defense: " + to_string(sword->getDefense())) << endl;
            cout << "> Inventory:" << endl;
            int idx = 0;
            vector<Item> rep;
            for(Item i: inventory){
                if(i.getType() == "sword"){
                    cout << "  - " << idx ++ << ": "<< i.getName() + " Attack: " + to_string(i.getAttack()) + " Defense: " + to_string(i.getDefense()) << endl;
                    rep.push_back(i);
                }
            }
            idx = -1;
            do{
                if(idx >= 0 && idx < (int)rep.size()){
                    Item* newed = new Item(rep[idx]);
                    setSword(newed);
                    break;
                }
                cout << "Enter the equipment you want to put on (Enter -1 to leave) > ";
            } while(cin >> idx && idx != -1);
        }
        else if(str == "sh"){
            clear();
            cout << "Shield: " << (shield == nullptr ? "(empty)" : (shield->getName()) + " Attack: " + to_string(shield->getAttack()) + " Defense: " + to_string(shield->getDefense())) << endl;
            cout << "> Inventory:" << endl;
            int idx = 0;
            vector<Item> rep;
            for(Item i: inventory){
                if(i.getType() == "shield"){
                    cout << "  - " << idx ++ << ": "<< i.getName() + " Attack: " + to_string(i.getAttack()) + " Defense: " + to_string(i.getDefense()) << endl;
                    rep.push_back(i);
                }
            }
            idx = -1;
            do{
                if(idx >= 0 && idx < (int)rep.size()){
                    Item* newed = new Item(rep[idx]);
                    setShield(newed);
                    break;
                }
                cout << "Enter the equipment you want to put on (Enter -1 to leave) > ";
            } while(cin >> idx && idx != -1);
        }    
    }
}

void Player::popPoison(int cnt){
    for(int i = 0; i < cnt; i ++){
        if(poison.size() == 0) break;
        poison.pop_back();
    }
}

void Player::popFood(Item _food){
    for(auto it=food.begin(); it!=food.end(); ++it){
        if(_food.getName() == it->getName()){
            food.erase(it);
            break;
        }
    }
}

void Player::useFood(Item food){
    // Hunger
    if(food.getHealth() != 0){
        hunger += food.getHealth();
    }
    // Thirst
    if(food.getAttack() != 0){
        thirst += food.getAttack();
    }
    // Poison
    if(food.getDefense() != 0){
        popPoison(food.getDefense());
    }
}

void Player::debuffStates(int hun, int thr){
    int difhun = hunger - hun;
    int difthr = thirst - thr;
    hunger = max(0, difhun);
    thirst = max(0, difthr);
    if(hunger == 0 || thirst == 0){
        setCurrentHealth(getCurrentHealth() + min(difhun, difthr));
    }
    if(poison.size() != 0){
        for(Item i: poison){
            setCurrentHealth(getCurrentHealth() - i.getDefense());
        }
    }
    if(getCurrentHealth() <= 0){
        cout << REDB << "Player " << getName() << " is dead." << NC << endl;
    }
}