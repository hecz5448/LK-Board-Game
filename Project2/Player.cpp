#include <iostream>
using namespace std;
#include "Player.h"

Player::Player(){
    _name = "";
    _strength = 0;
    _stamina = 0;
    _wisdom = 0;
    _pride_points = 0;
    _age = 0;
}
Player::Player(string name, int age, int strength, int stamina, int wisdom, int pridePoints){
    _name = name;
    _strength = strength;
    _stamina = stamina;
    _wisdom = wisdom;
    _pride_points = pridePoints;
    _age = age;
    _advisor = -1;
}
string Player::getName(){
    return _name;
}
int Player::getStrength(){
    return _strength;
}
int Player::getStamina(){
    return _stamina;
}
int Player::getWisdom(){
    return _wisdom;
}
int Player::getPridePoints(){
    return _pride_points;
}
int Player::getAge(){
    return _age;
}

int Player::getAdvisor(){
    return _advisor;
}
int Player::getStartingPath(){
    return _starting_path;
}

void Player::setStartingPath(int path){
    _starting_path = path;
}
void Player::setAdvisor(int advisor){
    _advisor = advisor;
}

void Player::setName(string name){
    _name = name;
}
void Player::setStrength(int strength){
    _strength = strength;
}
void Player::setStamina(int stamina){
    _stamina = stamina;
}
void Player::setWisdom(int wisdom){
    _wisdom = wisdom;
}
void Player::setPridePoints(int pridePoints){
    _pride_points = pridePoints;
}
void Player::setAge(int age){
    _age = age;
}

void Player::trainCub(){
    _strength += 200;
    _stamina += 200;
    _wisdom += 200;
    _pride_points -= 5000;
}
void Player::toPrideLands(){
    _strength += 200;
    _wisdom += 200;
    _stamina += 200;
    _pride_points += 5000;
}
void Player::printStats(){
    cout << _name << ", age " << _age << endl;
    cout << "Strength: " << _strength << endl;
    cout << "Stamina: " << _stamina << endl;
    cout << "Wisdom: " << _wisdom << endl;
    cout << "Pride Points: " << _pride_points << endl;
}


void Player::modifyStrength(int strength){
    _strength += strength;
}
void Player::modifyStamina(int stamina){
    _stamina += stamina;
}
void Player::modifyWisdom(int wisdom){
    _wisdom += wisdom;
}
void Player::modifyPridePoints(int pridePoints){
    _pride_points += pridePoints;
}
void Player::modifyAge(int age){
    _age += age;
}
