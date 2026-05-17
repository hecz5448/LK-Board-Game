#include <iostream>
#include "Player.h"
#include "Tile.h"
// #include "Board.h"

using namespace std;

int main(){
    Player Simba("Simba", 1000, 2000, 3000);
    Simba.printStats();
    Simba.setStamina(1500);
    Simba.printStats();
    return 0;
}
