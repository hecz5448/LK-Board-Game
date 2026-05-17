#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"
#include "Player.h"

class Board
{
private:
    static const int _BOARD_SIZE = 52;
    
    static const int _MAX_PLAYERS = 2;
    
    int _player_position[_MAX_PLAYERS];
    void displayTile(int player_index, int pos);
    void initializeTiles(int player_index);
    bool isPlayerOnTile(int player_index, int pos);
    int _player_count;
    

public:
    Tile _tiles[_MAX_PLAYERS][_BOARD_SIZE];
    Player _players[_MAX_PLAYERS];
    Board();
    Board(int player_count);
    void displayTrack(int player_index);
    void initializeBoard();
    void displayBoard();
    bool movePlayer(int player_index);
    int getPlayerPosition(int player_index) const;
    void initializeCubTraining(int player_index);
    void initializePridelands(int player_index);
    bool movePlayerBack(int player_index);
};

#endif