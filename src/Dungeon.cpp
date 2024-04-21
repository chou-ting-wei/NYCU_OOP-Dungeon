#include "../include/Dungeon.h"
#include "../include/General.h"
#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

bool Dungeon::passed = false;

Dungeon::Dungeon(){}
Record record;

void Dungeon::createPlayer(){
    clear();
    // figlet
    typewriter("________\n", 3);
    typewriter("\\______ \\  __ __  ____    ____   ____  ____   ____\n", 3);
    typewriter(" |    |  \\|  |  \\/    \\  / ___\\_/ __ \\/  _ \\ /    \\\n", 3);
    typewriter(" |    `   \\  |  /   |  \\/ /_/  >  ___(  <_> )   |  \\\n", 3);
    typewriter("/_______  /____/|___|  /\\___  / \\___  >____/|___|  /\\\n", 3);
    typewriter("        \\/           \\//_____/      \\/           \\/\n", 3);

    string name;
    cout << "\nPlease enter your name: ";
    getline(cin, name); 
    clear();
    player = Player(name, 150, 20, 20, 10, 10);
    cout << "Player " << name << ", welcome to the Dungeon Game!\n";
    cout << "Here are some survival rules:\n";
    cout << "1. There are four types of rooms: Normal, Desert, Forest, and Swamp. Each type has unique debuffs, items, NPCs, and more.\n";
    cout << "2. You can move up, down, left, or right. If you reach the exit room, you win the game.\n";
    cout << "3. You can interact with objects in the room, including monsters, NPCs, and items.\n";
    cout << "4. You can check your status, equipment, food, and manage game saves.\n";
    cout << "5. Eating food restores your hunger and thirst levels.\n";
    cout << "6. Equip items to increase your attack and defense stats.\n";
    cout << "7. You can save your game progress and load it later to continue playing.\n";
    cout << "8. If you die, you lose the game.\n";

    // moveToBottom();
    cout << "\nPress any key to start the game...";
    waitForKeypress();
    clear();
    player.triggerEvent(&player);
}

void Dungeon::createMap(){
    // Desert
    Monster* camel = new Monster("Camel", 30, 10, 5);
    Monster* rattlesnake = new Monster("Rattlesnake", 40, 15, 10);
    Monster* scorpion = new Monster("Scorpion", 55, 20, 30);

    // Forest
    Monster* fox = new Monster("Fox", 20, 10, 5);
    Monster* owl = new Monster("Owl", 40, 15, 15);
    Monster* bear = new Monster("Bear", 70, 30, 20);

    // Swamp
    Monster* aligator = new Monster("Aligator", 25, 10, 15);
    Monster* frog = new Monster("Frog", 30, 15, 20);
    Monster* heron = new Monster("Heron", 50, 25, 10);

    NPC* guide = new NPC("Guide Ko", "Welcome, player " + player.getName() + "!\nI'm Guide Ko.\nHere are some essentials to aid your journey.\nMake sure to equip yourself before venturing deeper into the dungeon.\n", vector<Item>{Item("Water_1", "food", 0, rng()%10 + 1, 0), Item("Chocolate", "food", rng()%10 + 1, 0, 0)});
    NPC* keeper = new NPC("Keeper Lee", "Hello!\nI'm Keeper Lee, guarding this place.\nTake care as you explore around here.\n", vector<Item>{Item("Milk_2", "food", 0, 0, rng()%3 + 1)});
    NPC* patrol = new NPC("Patrol Shun", "Hello there!\nPatrol Shun at your service.\nKeep your eyes open and stay safe!\n", vector<Item>{Item("Energy bar", "food", rng()%10 + 1, 0, 0)});
    NPC* merchant = new NPC("Merchant Kim", "Welcome!\nI'm Merchant Kim, and I have some special items just for you. Take a look!\n", vector<Item>{Item("Cheese biscuit", "food", rng()%10 + 1, 0, 0)});
    NPC* guide2 = new NPC("Guide Ko", "Great to see you again!\nYou've reached the end of the dungeon.\nHere are some rewards for your bravery.\nSafe travels!\n", vector<Item>{Item("Diamond Sword", "sword", 0, rng(), 0), Item("Diamond Shield", "shield", 0, 0, rng())});
    NPC* lake = new NPC("Lake", "Luckily, you stumbled upon a lake, where you can acquire water to replenish your thirst status.\n", vector<Item>{Item("Water_2", "food", 0, rng()%10 + 1, 0)});
    NPC* oasis = new NPC("Oasis", "Luckily, you stumbled upon an oasis, where you can acquire water to replenish your thirst status.\n", vector<Item>{Item("Water_3", "food", 0, rng()%10 + 1, 0)});

    Room* startRoom = new Room(false, "normal", 0, vector<Object*>{guide, new Item("Wood Sword", "sword", 0, rng()%10 + 1, 0)});
    Room* desert1 = new Room(false, "desert", 1, vector<Object*>{camel});
    Room* desert2 = new Room(false, "desert", 2, vector<Object*>{rattlesnake, new Item("Steel Shield", "shield", 0, 0, rng()%20 + 1)});
    Room* desert3 = new Room(false, "desert", 3, vector<Object*>{scorpion, new Item("Titanium Shield", "shield", 0, 0, rng()%40 + 1)});
    Room* desert4 = new Room(false, "desert", 4, vector<Object*>{oasis});
    Room* forest1 = new Room(false, "forest", 5, vector<Object*>{fox, new Item("Milk_1", "food", 0, 0, rng()%3 + 1)});
    Room* forest2 = new Room(false, "forest", 6, vector<Object*>{owl, new Item("Steel Sword", "sword", 0, rng()%20 + 1, 0)});
    Room* forest3 = new Room(false, "forest", 7, vector<Object*>{bear});
    Room* forest4 = new Room(false, "forest", 8, vector<Object*>{lake});
    Room* swamp1 = new Room(false, "swamp", 9, vector<Object*>{aligator, new Item("Wood Shield", "shield", 0, 0, rng()%10 + 1)});
    Room* swamp2 = new Room(false, "swamp", 10, vector<Object*>{frog});
    Room* swamp3 = new Room(false, "swamp", 11, vector<Object*>{heron, new Item("Titanium Sword", "sword", 0, rng()%40 + 1, 0)});
    Room* normal1 = new Room(false, "normal", 12, vector<Object*>{keeper});
    Room* normal2 = new Room(false, "normal", 13, vector<Object*>{patrol});
    Room* normal3 = new Room(false, "normal", 14, vector<Object*>{merchant});
    Room* exitRoom = new Room(true, string(GRN) + "exit"+ string(NC), 15, vector<Object*>{guide2});
    
    startRoom -> setUpRoom(desert1);

    desert1 -> setDownRoom(startRoom);
    desert1 -> setLeftRoom(swamp1);
    desert1 -> setRightRoom(forest1);

    // Left
    swamp1 -> setRightRoom(desert1);
    swamp1 -> setUpRoom(forest2);

    forest2 -> setDownRoom(swamp1);
    forest2 -> setUpRoom(normal3);

    normal3 -> setDownRoom(forest2);
    normal3 -> setRightRoom(desert3);

    desert3 -> setLeftRoom(normal3);
    desert3 -> setUpRoom(normal1);
    
    // Right
    forest1 -> setLeftRoom(desert1);
    forest1 -> setUpRoom(normal2);

    normal2 -> setDownRoom(forest1);
    normal2 -> setRightRoom(swamp2);

    swamp2 -> setLeftRoom(normal2);
    swamp2 -> setUpRoom(desert2);

    desert2 -> setDownRoom(swamp2);
    desert2 -> setUpRoom(forest4);

    forest4 -> setDownRoom(desert2);
    forest4 -> setLeftRoom(swamp3);

    swamp3 -> setRightRoom(forest4);
    swamp3 -> setLeftRoom(normal1);

    // Merge
    normal1 -> setRightRoom(swamp3);
    normal1 -> setDownRoom(desert3);
    normal1 -> setUpRoom(desert4);

    desert4 -> setDownRoom(normal1);
    desert4 -> setLeftRoom(forest3);

    forest3 -> setRightRoom(desert4);
    forest3 -> setLeftRoom(exitRoom);

    exitRoom -> setRightRoom(forest3);

    rooms.push_back(startRoom);
    rooms.push_back(desert1);
    rooms.push_back(desert2);
    rooms.push_back(desert3);
    rooms.push_back(desert4);
    rooms.push_back(forest1);
    rooms.push_back(forest2);
    rooms.push_back(forest3);
    rooms.push_back(forest4);
    rooms.push_back(swamp1);
    rooms.push_back(swamp2);
    rooms.push_back(swamp3);
    rooms.push_back(normal1);
    rooms.push_back(normal2);
    rooms.push_back(normal3);
    rooms.push_back(exitRoom);

    player.setCurrentRoom(startRoom);
}

void Dungeon::handleMovement(){
    map<char, Room*> avaRoom;
    if(player.getCurrentRoom() -> getUpRoom() != nullptr
        || player.getCurrentRoom() -> getDownRoom() != nullptr
        || player.getCurrentRoom() -> getLeftRoom() != nullptr
        || player.getCurrentRoom() -> getRightRoom() != nullptr){
        if(player.getCurrentRoom() -> getUpRoom() != nullptr){
            avaRoom['U'] = avaRoom['u'] = player.getCurrentRoom() -> getUpRoom();
            cout << "(U)p Room" << endl;
        }
        if(player.getCurrentRoom() -> getDownRoom() != nullptr){
            avaRoom['D'] = avaRoom['d'] = player.getCurrentRoom() -> getDownRoom();
            cout << "(D)own Room" << endl;
        }
        if(player.getCurrentRoom() -> getLeftRoom() != nullptr){
            avaRoom['L'] = avaRoom['l'] = player.getCurrentRoom() -> getLeftRoom();
            cout << "(L)eft Room" << endl;
        }
        if(player.getCurrentRoom() -> getRightRoom() != nullptr){
            avaRoom['R'] = avaRoom['r'] = player.getCurrentRoom() -> getRightRoom();
            cout << "(R)ight Room" << endl;
        }
        if(player.getCurrentRoom() -> getIsExit() == true){
            avaRoom['E'] = avaRoom['e'] = nullptr;
            cout << "(E)xit" << endl;
        }
        char c;
        do{
            cout << "Which room do you want to go? > ";
        } while(cin >> c && avaRoom.find(c) == avaRoom.end());
        if(c == 'E' || c == 'e'){
            clear();
            cout << GRN << "Congratulations! Player " << player.getName() << ", you have exited the dungeon." << NC << endl;
            player.setCurrentRoom(nullptr);
            passed = true;
        }
        else{
            player.changeRoom(avaRoom[c]);
            string roomType = player.getCurrentRoom()->getType();
            int hungerConsumption = (roomType == "forest" ? 4 : (roomType == "swamp" ? 2 : (roomType == "desert" ? 1 : 0)));
            int thirstConsumption = (roomType == "desert" ? 4 : (roomType == "swamp" ? 2 : (roomType == "forest" ? 1 : 0)));

            if(roomType == "swamp"){
                int poisonRng = rng()%5 + 1;
                player.addPoison(Item("Poison_" + to_string(poisonRng), "poison", 0, 0, poisonRng));
            }
            player.debuffStates(hungerConsumption, thirstConsumption);
        }
    } 
    else {
        cout << "Sorry, you can't go anywhere." << endl;
    }

    return;
}


void Dungeon::handleEvent(Object* object){
    object -> triggerEvent(&player);
    return;
}

bool Dungeon::checkGameLogic(){
    if(player.getCurrentRoom() == nullptr || player.getCurrentHealth() <= 0) return false;
    else return true;
}

void Dungeon::chooseAction(vector<Object*> objects){
    int idx = 0;
    string roomType = player.getCurrentRoom()->getType();
    int hungerConsumption = (roomType == "forest" ? 4 : (roomType == "swamp" ? 2 : (roomType == "desert" ? 1 : 0)));
    int thirstConsumption = (roomType == "desert" ? 4 : (roomType == "swamp" ? 2 : (roomType == "forest" ? 1 : 0)));
    for(int i = 0; i < (int)objects.size(); i++){
        if(objects[i]->getTag() == "Monster"){
            clear();
            cout << "------------------- ROOM -------------------" << endl;
            cout << "> Room type: " << roomType << endl;
            cout << "> Hunger consumption: " << hungerConsumption << endl;
            cout << "> Thirst consumption: " << thirstConsumption << endl;
            if(roomType == "swamp") cout << "> " << RED << "You are poisoned!" << NC << endl;
            cout << "--------------------------------------------" << endl;
            handleEvent(objects[i]);
            return;
        }
    }
    cout << "------------------- ROOM -------------------" << endl;
    cout << "> Room type: " << roomType << endl;
    cout << "> Hunger consumption: " << hungerConsumption << endl;
    cout << "> Thirst consumption: " << thirstConsumption << endl;
    if(roomType == "swamp") cout << "> " << RED << "You are poisoned!" << NC << endl;

    for(int i=0;i<(int)objects.size();i++){
        cout << idx ++ << ": " << CYN + (objects[i]->getTag() == "Item" ? dynamic_cast<Item*>(objects[i])->getType() : objects[i]->getTag()) + NC << 
        " " << objects[i]->getName() << endl;
    }
    cout << "--------------------------------------------" << endl;
    cout << "(M)ove" << endl;
    cout << "(S)how Status" << endl;
    cout << "(E)quipment" << endl;
    cout << "(F)ood" << endl;
    cout << "(C)reate Record" << endl;
    cout << "(L)oad Record" << endl;
    cout << "(Q)uit" << endl;
    char c;
    do{
        cout << "Enter the instruction or the index of the charcter you want to interact: > ";
        c = tolower(c);
        if(('0' <= c && c < '0'+(int)objects.size()) || c == 'm' || c == 's' || c == 'e' || c == 'f' || c == 'c' || c == 'l' || c == 'q') break;
    } while(cin >> c);
    clear();
    if(c == 'm'){
        handleMovement();
        // clear();
    } 
    else if(c == 's'){
        player.triggerEvent(&player);
    } 
    else if(c == 'e'){
        player.equip();
        clear();
    } 
    else if(c == 'f'){
        int inp = -2;
        do {
            cout << "------------------- FOOD -------------------" << endl;
            int sz = player.getFood().size();
            if(0 <= inp && inp < sz){
                player.useFood(player.getFood()[inp]);
                player.popFood(player.getFood()[inp]);
            }
            int idx = 0;
            for(auto i: player.getFood()){
                cout << idx << ": " << i.getName() << " usage: ";
                // Hunger
                if(i.getHealth() != 0){
                    cout << "Restore " << i.getHealth() << " hunger" << endl;
                }
                // Thirst
                if(i.getAttack() != 0){
                    cout << "Restore " << i.getAttack() << " thirst" << endl;
                }
                // Poison
                if(i.getDefense() != 0){
                    cout << "Remove " << i.getDefense() <<" poison" << endl;
                }
                idx ++;
            }
            cout << "--------------------------------------------" << endl;
            cout << "Which food you want to eat (-1 for quit) > ";
        } while(cin >> inp && inp != -1);
        clear();
    }
    else if(c == 'c'){
        record.saveToFile(&player, rooms);
    }
    else if(c == 'l') {
        record.loadFromFile(&player, rooms);
    }
    else if(c == 'q'){
        exit(0);
    }
    else {
        handleEvent(objects[c-'0']);
        if(objects[c-'0']->getTag()=="Item"){
            player.getCurrentRoom()->popObject(objects[c-'0']);
        }
        clear();
    }
}

void Dungeon::startGame(){
    createPlayer();
    createMap();
}

void Dungeon::runDungeon(){
    startGame();
    while(!passed){
        if(checkGameLogic() == false){
            exit(0);
        }
        chooseAction(player.getCurrentRoom() -> getObjects());
    }
}