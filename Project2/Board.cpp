#include "Board.h"
#include "Game.h"
#include "Player.h"
#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"  /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"

void Board::initializeBoard()
{
    // Seed random number generator in your main function once
    for (int i = 0; i < 2; i++)
    {
        initializeTiles(i);  // This ensures each lane has a unique tile distribution
    }
}

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()


void Board::initializeCubTraining(int player_index)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    //specific odds for cub training 
    for (int i = 0; i < total_tiles; i++)
        {
            if (i == total_tiles - 1) {
                // Set the last tile as Orange for "Pride Rock"
                temp.color = 'O';
            } 
            else if (i == 0) {
                // Set the first tile as Grey for starting place
                temp.color = 'Y';
            } 
            else if (green_count < 20 && (rand() % (total_tiles - i) < 20 - green_count)) {
                temp.color = 'G';
                green_count++;
            }
            else
            {
                // Randomly assign one of the other colors (special tiles): Blue, Pink, Brown, Red, Purple
                int color_choice = rand() % 100;
                if (color_choice >= 0 && color_choice < 20) // 20% chance for oasis because their advisor and training helps them find more
                {
                    temp.color = 'B'; // Blue (Oasis)
                }
                else if (color_choice >= 20 && color_choice < 30) // 10% chance for advisor since they are loyal to their mentor who trained them as a cub so they don't try to look for another
                {
                    temp.color = 'P'; // Pink (Counseling)
                }
                else if (color_choice >= 30 && color_choice < 50) // 20% chance for hyena since their advisor helps them to avoid them
                {
                    temp.color = 'N'; // Brown (Hyenas)
                }
                else if (color_choice >= 50 && color_choice < 70) //20% chance for graveyard as well because of their advisor guiding them
                {
                    temp.color = 'R'; // Red (Graveyard)
                }
                else if (color_choice >= 70 && color_choice < 100) //30% chance for challenge because they feel strong and want to prove themselves to their advisor
                {
                    temp.color = 'U'; // Purple (Challenge)
                }
            }
            // Assign the tile to the board for the specified lane
            _tiles[player_index][i] = temp;
        }
    // Assign the tile to the board for the specified lane
}
void Board::initializePridelands(int player_index)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    //specific odds for straight to the pridelands 
    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        } 
        else if (i == 0) {
            // Set the first tile as Grey for starting place
            temp.color = 'Y';
        } 
        else if (green_count < 20 && (rand() % (total_tiles - i) < 20 - green_count)) {
            temp.color = 'G';
            green_count++;
        }
        else{
        // Randomly assign one of the other colors (special tiles): Blue, Pink, Brown, Red, Purple
            int color_choice = rand() % 100;
            if (color_choice >= 0 && color_choice < 15) // 15% chance for oasis
            {
                temp.color = 'B'; // Blue (Oasis)
            }
            else if (color_choice >= 15 && color_choice < 35) // 20% chance for advisor since they are on their own and are looking for a companion
            {
                temp.color = 'P'; // Pink (Counseling)
            }
            else if (color_choice >= 35 && color_choice < 50) // 25% chance for hyena since overconfidence leads the player to wander
            {
                temp.color = 'N'; // Brown (Hyenas)
            }
            else if (color_choice >= 50 && color_choice < 75) //25% chance for graveyard as well because of wandering
            {
                temp.color = 'R'; // Red (Graveyard)
            }
            else if (color_choice >= 75 && color_choice < 100) //25% chance for challenge
            {
                temp.color = 'U'; // Purple (Challenge)
            }
        _tiles[player_index][i] = temp;
        }
    }
    // Assign the tile to the board for the specified lane
}
void Board::initializeTiles(int player_index){
    
    if (_players[player_index].getStartingPath() == 1)
    {
    initializeCubTraining(player_index);
    }
    else if (_players[player_index].getStartingPath() == 2)
    {
    initializePridelands(player_index);
    }
    else {
        initializeCubTraining(player_index);
    }
}

Board::Board()
{
    _player_count = 1;

    // Initialize player position
    _player_position[0] = 0;

    // Initialize tiles
    //initializeTiles(); // not sure this is necessary in board constructor
}

Board::Board(int player_count)
{
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }

    // Initialize player position
    for (int i = 0; i < _player_count; i++)
    {
        _player_position[i] = 0;
    }

    // Initialize tiles

    initializeBoard();
}

bool Board::isPlayerOnTile(int player_index, int pos)
{
    if (_player_position[player_index] == pos)
    {
        return true;
    }
    return false;
}

void Board::displayTile(int player_index, int pos)
{
    // string space = "                                       ";
    string color = "";
    int player = isPlayerOnTile(player_index, pos);

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display
    if (_tiles[player_index][pos].color == 'R')
    {
        color = RED;
    }
    else if (_tiles[player_index][pos].color == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[player_index][pos].color == 'B')
    {
        color = BLUE;
    }
    else if (_tiles[player_index][pos].color == 'U')
    {
        color = PURPLE;
    }
    else if (_tiles[player_index][pos].color == 'N')
    {
        color = BROWN;
    }
    else if (_tiles[player_index][pos].color == 'P')
    {
        color = PINK;
    }
    else if (_tiles[player_index][pos].color == 'O')
    {
        color = ORANGE;
    }
    else if (_tiles[player_index][pos].color == 'Y')
    {
        color = GREY;
    }

    if (player == true)
    {
        cout << color << "|" << (player_index + 1) << "|" << RESET;
    }
    else
    {
        cout << color << "| |" << RESET;
    }
}

void Board::displayTrack(int player_index)
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(player_index, i);
    }
    cout << endl;
}

void Board::displayBoard()
{
    for (int i = 0; i < 2; i++)
    {
        displayTrack(i);
        if (i == 0) {
            cout << endl;  // Add an extra line between the two lanes
        }
    }
}

bool Board::movePlayer(int player_index)
{
    // Increment player position
    _player_position[player_index]++;
    if (_player_position[player_index] == _BOARD_SIZE - 1)
    {
        // Player reached last tile
        return true;
    }
    return false;
}

bool Board::movePlayerBack(int player_index)
{
    // Increment player position
    _player_position[player_index]--;
    if (_player_position[player_index] == _BOARD_SIZE - 51)
    {
        // Player reached first tile
        return true;
    }
    return false;
}

int Board::getPlayerPosition(int player_index) const
{
    if (player_index >= 0 && player_index <= _player_count)
    {
        return _player_position[player_index];
    }
    return -1;
}