#include <iostream>
#include "Game.h"
#include "Board.h"
#include "Tile.h"
#include "Player.h"
#include <cstdlib> // For rand() and srand()
#include <ctime> 
using namespace std;

int main(){
    srand(time(0)); //seed once for different experience each time
    Game g;
    g.setupGame(); //setup board and read files

    int winnerIndex;
    while (g.getGameEnded() == false) {
        for(int i = 0; i < 2; i++){ // runs for each player
            g.playTurn(i);
            winnerIndex = i;
        }
    }
    
    cout << "Player " << winnerIndex+1 << " has reached the end!" << endl;
    for (int i = 0; i < 2; i++){
        g.calculateFinalPride(i);
    }
    g.displayWinner();

        // run function to let players turn their leadership traits into pride points
        //run function that displays and determines the winner with their final pride points
    return 0;
}