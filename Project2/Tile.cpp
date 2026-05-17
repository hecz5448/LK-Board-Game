#include <iostream>
#include <fstream>
#include "Tile.h"
#include "Player.h"
using namespace std;

Tile::Tile(){
    color = ' ';
}
char Tile::getColor(){
    return color;
}

void Tile::setColor(char c){
    color = c;
}


