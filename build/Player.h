#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"
#include "Room.h"

using namespace std;

class Item;

class Player: public GameCharacter
{
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Item> inventory;
public:
    Player();
    Player(string,int,int,int);
    void addItem(Item);
    void increaseStates(int,int,int);
    void changeRoom(Room*);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInventory(vector<Item>);
    Room* getCurrentRoom();
    Room* getPreviousRoom();

    vector<Item> getInventory();
    Item* getHead();
    Item* getLeft();
    Item* getRight();
    Item* getBody();
    vector<Item> getPotions();
    vector<Item> getKeys();

    void setHead(Item*);
    void setLeft(Item*);
    void setRight(Item*);
    void setBody(Item*);
    void addKey(Item);
    void addPotions(Item);
    void popKey(Item);
    void useHealPotion(Item);
    void popPotions(Item);
    void equip();
};

#endif // PLAYER_H_INCLUDED
