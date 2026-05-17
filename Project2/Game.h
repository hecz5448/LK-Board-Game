#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Player.h"
#include "Tile.h"
#include "Board.h"

using namespace std;

struct Riddle
{
    string question;
    string answer;
};

struct Character
{
    string name;
    int age;
    int stamina;
    int strength;
    int wisdom;
    int pridePoints;
};
struct Event
{
    string eventMessage;
    int pathType;
    int advisor;
    int pridePoints;
};

class Game
{
    private:

    int _player_count;


    Board _board;

    static const int _MAX_RIDDLES = 40;
    Riddle _riddles[_MAX_RIDDLES];
    int _riddle_count;

    static const int _MAX_CHARACTERS = 10;
    Character _characters[_MAX_CHARACTERS];
    int _character_count;

    static const int _MAX_EVENTS = 70;
    Event _events[_MAX_EVENTS];
    int _event_count;

    bool _game_ended;



    public:
    Game();
    // int getAdvisor(int player_index);
    // int setAdvisor(int player_index, int advisor);

    bool getGameEnded();
    void loadRiddle(string filename, const int arr_size);
    void loadCharacter(string filename, const int arr_size);
    void loadEvent(string filename, const int arr_size);

    Player playRiddle(Player p, const int riddle_count);
    Player playEvent(Player p, const int event_count);

    void playChallenge(int player_index);
    void playOasis(int player_index);
    void playGraveyard (int player_index);
    void playHyena(int player_index);
    void playAdvisor(int player_index);

    void playTurn(int player_index);
    void setupGame();

    void calculateFinalPride(int player_index);
    // bool isGameFinished(); //will checks if a player has reached the final tile
    void displayWinner(); //will display who won and will use printstats to show the final stats of each player
    



};
#endif

