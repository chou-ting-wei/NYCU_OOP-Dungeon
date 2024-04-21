#include "Object.h"

Object::Object(){
    name = "";
    tag = "";
}
 
Object::Object(string name, string tag){
    this->name = name;
    this->tag = tag;
}
 
void Object::setName(string name){
    this->name = name;
}
 
void Object::setTag(string tag){
    this->tag = tag;
}
 
string Object::getName(){
    return name;
}
 
string Object::getTag(){
    return tag;
}