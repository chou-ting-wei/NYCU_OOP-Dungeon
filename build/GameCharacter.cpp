#include "GameCharacter.h"

GameCharacter::GameCharacter() : Object(){
    maxHealth = 0;
    currentHealth = 0;
    attack = 0;
    defense = 0;
}

GameCharacter::GameCharacter(string name, string tag, int maxHealth, int attack, int defense) : Object(name, tag){
    this->maxHealth = maxHealth;
    this->currentHealth = maxHealth;
    this->attack = attack;
    this->defense = defense;
}

bool GameCharacter::checkIsDead(){
    return this->currentHealth <= 0;
}

int GameCharacter::takeDamage(int damage){
    return this->currentHealth -= damage;
}

void GameCharacter::setMaxHealth(int maxHealth){
    this->maxHealth = maxHealth;
}

void GameCharacter::setCurrentHealth(int currentHealth){
    this->currentHealth = currentHealth;
}

void GameCharacter::setAttack(int attack){
    this->attack = attack;
}

void GameCharacter::setDefense(int defense){
    this->defense = defense;
}

int GameCharacter::getMaxHealth(){
    return maxHealth;
}

int GameCharacter::getCurrentHealth(){
    return currentHealth;
}

int GameCharacter::getAttack(){
    return attack;
}

int GameCharacter::getDefense(){
    return defense;
}