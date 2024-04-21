#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"

using namespace std;

class Monster: public GameCharacter
{
private:
    bool isBoss;
public:
    Monster();
    Monster(string,int,int,int);

    bool getIsBoss();
    void setIsBoss(int);
    void printStatus();

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object*);
};


#endif // ENEMY_H_INCLUDED
