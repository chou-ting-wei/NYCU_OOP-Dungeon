#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <cctype> 
#include <algorithm> 
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Item;

class Player: public GameCharacter
{
private:
    Room* currentRoom = nullptr;
    Room* previousRoom = nullptr;
    Item* sword = nullptr;
    Item* shield = nullptr;
    vector<Item> inventory;
    vector<Item> food;
    vector<Item> poison;
    int hunger;
    int thirst;
public:
    Player();
    Player(string, int, int, int, int, int);
    void addItem(Item);
    void increaseStates(int, int, int);
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
    Item* getSword();
    Item* getShield();
    vector<Item> getInventory();
    vector<Item> getFood();
    vector<Item> getPoison();
    int getHunger();
    int getThirst();

    void setSword(Item*);
    void setShield(Item*);
    void addFood(Item);
    void addPoison(Item);
    void setHunger(int);
    void setThirst(int);

    void equip();
    void popPoison(int);
    void popFood(Item);
    void useFood(Item);
    
    void debuffStates(int, int);
};

#endif // PLAYER_H_INCLUDED