#include <iostream>
#include "Player.h"
#include "Tile.h"
#include "Board.h"
#include "Game.h"
#include <fstream>
#include <cstdlib>
using namespace std;

int split(string input, char delim, string tokens[], const int ARR_SIZE)
{
    string token = "";
    int count = 0;
    int length = input.length();
    if (input.length() == 0)
    {
        return 0;
    }

    for (int i = 0; i < length; i++)
    {
        if (input.at(i) == delim)
        {
            if (count == ARR_SIZE)
            {
                return -1;
            }
            tokens[count] = token;
            token = "";
            count++;
        }
        else
        {
            token += input.at(i);
        }
    }

    if (count == ARR_SIZE)
    {
        return -1;
    }
    tokens[count] = token;
    token = "";
    count++;

    return count;
}


Game::Game(){
    _player_count = 2;
    _board = Board(_player_count);
    _riddle_count = 26;
    _character_count = 5;
    _event_count = 49;
    _game_ended = false;
    for (int i = 0; i < _player_count; i++)
    {
        _board._players[i] = Player(" ", 0, 0, 0, 0, 0);
    }
}
bool Game::getGameEnded(){
    return _game_ended;
}


void Game::loadCharacter(string filename, const int arr_size){
    ifstream infile(filename);
    string line;
    if (infile.fail()){
        return; // if file fails to open stop the function
    }

    getline(infile, line); // read the header line
    

    string stats[6];
    int i = 0;
    while (getline(infile, line)){
        split(line, '|', stats, 6);
        
        _characters[i].name = stats[0];
        _characters[i].age = stoi(stats[1]);
        _characters[i].stamina = stoi(stats[2]);
        _characters[i].strength = stoi(stats[3]);
        _characters[i].wisdom = stoi(stats[4]);
        _characters[i].pridePoints = stoi(stats[5]);
        i++;
    }
}

void Game::loadRiddle(string filename, const int arr_size)
{
    ifstream infile(filename);
    string line;
    if (infile.fail()){
        return; // if file fails to open stop the function
    }

    getline(infile, line); // read the header line

    string arr[2];
    int i = 0;
    while (getline(infile, line)){
       
        split(line, '|', arr, 2);
        _riddles[i].question = arr[0];
        _riddles[i].answer = arr[1];
        i++;
    }
}

void Game::loadEvent(string filename, const int arr_size)
{
    ifstream infile(filename);
    string line;
    if (infile.fail()){
        return; // if file fails to open stop the function
    }

    getline(infile, line); // read the header line
    string arr[4];
    int i = 0;
    while (getline(infile, line)){
        
        split(line, '|', arr, 4);
        
        _events[i].eventMessage = arr[0];
        // _events[i].pathType = stoi(arr[1]);
        // _events[i].advisor  = stoi(arr[2]);
        // _events[i].pridePoints = stoi(arr[3]);
        i++;
    }
}

Player Game::playEvent(Player p, const int event_count)
{
    int selected_index = rand() % (event_count);
    while (_events[selected_index].pathType != p.getStartingPath()){ // keep rolling for an event that matches the player's advisor and path type
        selected_index = rand() % (event_count);
    }
    
    string message = _events[selected_index].eventMessage;
    int pridePoints = _events[selected_index].pridePoints; 
    cout << message << endl; 
    // print event message and increase/decrease pridepoints based on the event
    if (p.getAdvisor() != _events[selected_index].advisor){ // prevent loss of points if advisor matches up
    p.modifyPridePoints(pridePoints);
    }
    else {
        cout << "You avoided this with your advisors guidance which saved you from losing some pride points" << endl;
    }
    return p;
}

Player Game::playRiddle(Player p, const int riddle_count)
{
    int selected_index = rand() % (riddle_count);
    string question = _riddles[selected_index].question;
    string answer = _riddles[selected_index].answer;
    cout << question << endl; 

    string input;
    cin >> input; // read user's answer 
    if (input == answer){
        p.modifyWisdom(500); //increase wisdom 500
        cout << "Correct! A smart answer grants you +500 wisdom." << endl;
    }
    else {
        cout << "Unfortunately that is incorrect. More Challenges await you in the future." << endl;
    }

    return p;
}

void Game::playOasis(int player_index) {
    _board._players[player_index].modifyStamina(200);
    _board._players[player_index].modifyStrength(200); //stats go up 200
    _board._players[player_index].modifyWisdom(200);

    // extra turn
    cout << "You have found a peaceful oasis! This grants the player an extra turn to keep moving forward, take a deep breath, and relax; you also gain 200 Stamina, Strength, and Wisdom Points." << endl;
}
void Game::playGraveyard(int player_index){
    // move back 10 tiles
    for (int i = 0; i < 10; i++){
        bool isFirstTile =_board.movePlayerBack(player_index);
        if (isFirstTile == true){
            break;
        }
    }   
    _board._players[player_index].modifyStamina(-100);
    _board._players[player_index].modifyStrength(-100); //stats go down 100
    _board._players[player_index].modifyWisdom(-100);

    cout << "Oh no! Its a graveyard... -100 to Stamina Strength and Wisdom and move back 10 tiles :(" << endl;
} 
void Game::playAdvisor(int player_index){
    cout << "Welcome to the land of enrichment, your Stamina, Strength, and Wisdom Points increase by 300, and you get to choose an advisor from the available list of advisors." << endl
    << "If you already have an advisor, you can switch your advisor out for a different one from the list or keep your original advisor." << endl 
    << "Do not forget - an advisor can protect you from random events that negatively impact your Pride Points." << endl;
    _board._players[player_index].modifyStamina(300);
    _board._players[player_index].modifyStrength(300); //stats go up 300
    _board._players[player_index].modifyWisdom(300);
    //choose advisor 
    int advisor = _board._players[player_index].getAdvisor();
    int wantsNewAdvisor = 0;
    if (advisor == 1)
    {
        cout << "Your advisor is Rafiki" << endl
        << "Would you like a new advisor? (1) Yes (2) No" << endl;
        cin >> wantsNewAdvisor;
        if (wantsNewAdvisor != 1 && wantsNewAdvisor != 2){
            cout << "Please select (1) for a new advisor or (2) to keep your old one" << endl;
            cin >> wantsNewAdvisor;
        }
    }
    else if (advisor == 2)
    {
        cout << "Your advisor is Nala" << endl
        << "Would you like a new advisor? (1) Yes (2) No" << endl;
        cin >> wantsNewAdvisor;
        if (wantsNewAdvisor != 1 && wantsNewAdvisor != 2){
            cout << "Please select (1) for a new advisor or (2) to keep your old one" << endl;
            cin >> wantsNewAdvisor;
        }
    }
    else if (advisor == 3)
    {
        cout << "Your advisor is Sarabi" << endl
        << "Would you like a new advisor? (1) Yes (2) No" << endl;
        cin >> wantsNewAdvisor;
        if (wantsNewAdvisor != 1 && wantsNewAdvisor != 2){
            cout << "Please select (1) for a new advisor or (2) to keep your old one" << endl;
            cin >> wantsNewAdvisor;
        }
    }
    else if (advisor == 4)
    {
        cout << "Your advisor is Zazu" << endl
        << "Would you like a new advisor? (1) Yes (2) No" << endl;
        cin >> wantsNewAdvisor;
        if (wantsNewAdvisor != 1 && wantsNewAdvisor != 2){
            cout << "Please select (1) for a new advisor or (2) to keep your old one" << endl;
            cin >> wantsNewAdvisor;
        }
    }
    else if (advisor == 5)
    {
        cout << "Your advisor is Sarafina" << endl
        << "Would you like a new advisor? (1) Yes (2) No" << endl;
        cin >> wantsNewAdvisor;
        if (wantsNewAdvisor != 1 && wantsNewAdvisor != 2){
            cout << "Please select (1) for a new advisor or (2) to keep your old one" << endl;
            cin >> wantsNewAdvisor;
        }
    }

    if (wantsNewAdvisor == 1 || advisor == -1){ // wants new one or doesnt have one
        cout << "Choose a new advisor" << endl
        << "1. Rafiki - Invisibility (the ability to become un-seen)" << endl
        << "2. Nala - Night Vision (the ability to see clearly in darkness)" << endl
        << "3. Sarabi - Energy Manipulation (the ability to shape and control the properties of energy)" << endl
        << "4. Zazu - Weather Control (the ability to influence and manipulate weather patterns)" << endl
        << "5. Sarafina - Super Speed (the ability to run 4x faster than the maximum speed of lions)" << endl;
        cin >> advisor;
        _board._players[player_index].setAdvisor(advisor);
    }
    
    //change advisor if you already have one

}
void Game::playHyena(int player_index){
    cout << "The Hyenas are on the prowl! They drag you back to where you were last, and the journey comes at a cost." << endl
<< "This moves the player back a Tile. In addition, the players Stamina Points decrease by 300 Points." << endl;
    _board._players[player_index].modifyStamina(-300);
    _board.movePlayerBack(player_index);
}
void Game::playChallenge(int player_index){
    _board._players[player_index] = playRiddle(_board._players[player_index], _riddle_count); 
}

void Game::calculateFinalPride(int player_index){
    
    _board._players[player_index].modifyPridePoints((_board._players[player_index].getStrength()*10) +(_board._players[player_index].getStamina()*10) + (_board._players[player_index].getWisdom()*10));
    // add 10x of each stat to pride points
}
void Game::displayWinner(){

    if (_board._players[0].getPridePoints() > _board._players[1].getPridePoints()){
        cout << "Player 1 has won with " << _board._players[0].getPridePoints() << " Pride Points" << endl;
        cout << "Player 2  with fought hard ending with " << _board._players[1].getPridePoints() << " Pride Points" ;
    }
    else {
        cout << "Player 2 has won with " << _board._players[1].getPridePoints() << " Pride Points" << endl;
        cout << "Player 1  with fought hard ending with " << _board._players[0].getPridePoints() << " Pride Points" ;
    }
}

void Game::playTurn(int player_index){
    cout << "Player " << player_index+1 << " " << _board._players[player_index].getName() << endl
    << "Main Menu: Select an option to continue" << endl
    << "1. Convert Leadership Traits Into Pridepoints (1)" << endl
    << "2. Review Character (2)" << endl
    << "3. Check Position (3)" << endl
    << "4. Review your Advisor (4)" << endl
    << "5. Move Forward (5)" << endl;

    bool isFinalTile = false;
    int player_choice = 0;
    int secondaryChoice = 0;
    int tertiaryChoice = 0;
    cin >> player_choice;
    if (player_choice <= 0 || player_choice > 5){
        cout << "Please choose an option using the corresponding number" << endl;
        cin >> player_choice;
    }
    else if (player_choice == 1){ 
        cout << "You have " << _board._players[player_index].getPridePoints() << " Pride Points" << endl
        << "Would you like to convert leadership traits to get more pride points? (1) Yes (2) No" << endl;
        cin >> secondaryChoice;
        if (secondaryChoice == 1){
            _board._players[player_index].printStats();
            cout << "Which trait would you like to convert to pride points? (1) Strength (2) Stamina (3) Wisdom " << endl;
            cin >> secondaryChoice;
            cout << "How many would you like to convert?" << endl;
            cin >> tertiaryChoice;
            if (secondaryChoice == 1){
                if (tertiaryChoice <= _board._players[player_index].getStrength()){
                    _board._players[player_index].modifyStrength(-tertiaryChoice);
                    _board._players[player_index].modifyPridePoints(10*tertiaryChoice);
                }
                else {
                    cout << "You cannot convert more than you have." << endl;
                }
            } 
            else if (secondaryChoice == 2){
                if (tertiaryChoice <= _board._players[player_index].getStamina()){
                    _board._players[player_index].modifyStamina(-tertiaryChoice);
                    _board._players[player_index].modifyPridePoints(10*tertiaryChoice);
                }
                else {
                    cout << "You cannot convert more than you have." << endl;
                }
            }
            else if (secondaryChoice == 3){
                if (tertiaryChoice <= _board._players[player_index].getWisdom()){
                    _board._players[player_index].modifyWisdom(-tertiaryChoice);
                    _board._players[player_index].modifyPridePoints(10*tertiaryChoice);
                }
                else {
                    cout << "You cannot convert more than you have." << endl;
                }
            }

        
        }
        playTurn(player_index);
    }
    else if (player_choice == 2){
        _board._players[player_index].printStats();
        playTurn(player_index);
    }
    else if (player_choice == 3){
        int pos =_board.getPlayerPosition(player_index);
        cout << "Your position is tile " << pos << endl;
        playTurn(player_index);
    }
    else if (player_choice == 4){
        
        // check for which advisor the player has and output what the advisor does 
        int advisor = _board._players[player_index].getAdvisor();
        if (advisor == -1){
            cout << "You do not yet have an advisor" << endl;
        }
        if (advisor == 1)
        {
            cout << "Your advisor is Rafiki" << endl
            << "Review ability? (1) Yes (2) No" << endl;
            cin >> secondaryChoice;
            if (secondaryChoice == 1){
                cout << "Rafikis ability is Invisibility (the ability to become un-seen)" << endl;
            }
        }
        else if (advisor == 2)
        {
            cout << "Your advisor is Nala" << endl
            << "Review ability? (1) Yes (2) No" << endl;
            cin >> secondaryChoice;
            if (secondaryChoice == 1){
                cout << "Nalas ability is Night Vision (the ability to see clearly in darkness)" << endl;
            }
        }
        else if (advisor == 3)
        {
            cout << "Your advisor is Sarabi" << endl
            << "Review ability? (1) Yes (2) No" << endl;
            cin >> secondaryChoice;
            if (secondaryChoice == 1){
                cout << "Sarabis ability is Energy Manipulation (the ability to shape and control the properties of energy)" << endl;
            }
        }
        else if (advisor == 4)
        {
            cout << "Your advisor is Zazu" << endl
            << "Review ability? (1) Yes (2) No" << endl;
            cin >> secondaryChoice;
            if (secondaryChoice == 1){
                cout << "Zazus ability is Weather Control (the ability to influence and manipulate weather patterns)" << endl;
            }
        }
        else if (advisor == 5)
        {
            cout << "Your advisor is Sarafina" << endl
            << "Review ability? (1) Yes (2) No" << endl;
            cin >> secondaryChoice;
            if (secondaryChoice == 1){
                cout << "Sarafinas ability is Super Speed (the ability to run 4x faster than the maximum speed of lions)" << endl;
            }
        }
        playTurn(player_index);
    }
    else if (player_choice == 5){
        int movementNum = rand() % 6;
        for (int i = 0; i < movementNum+1; i++){
            isFinalTile = _board.movePlayer(player_index);
            if (isFinalTile == true){
                _game_ended = true;
            }
        }   
        int pos = _board.getPlayerPosition(player_index);
        cout << "Your new position is tile " << pos-1 << endl;
        char color = _board._tiles[player_index][pos].getColor();
        // find color of tile at player position and set color = to it
        
        if (color == 'R')
        {
            playGraveyard(player_index);
        }
        else if (color == 'G')
        {
            int chance = rand() % 2; //50% chance for event to happen on green tile
            if (chance == 1){
                playEvent(_board._players[player_index], _event_count);
            }
            else {
                cout << "Empty grasslands, nothing happened..." << endl;
            }
        }
        else if (color == 'B')  // run different functions depending on tile color
        {
            playOasis(player_index);
             // extra turn
        }
        else if (color == 'U')
        {
            cout << "RIDDLE TILE!!" << endl;
            playChallenge(player_index);
        }
        else if (color == 'N')
        {
            playHyena(player_index);
        }
        else if (color == 'P')
        {
            playAdvisor(player_index);
        }
        _board.displayBoard();
    }
}

void Game::setupGame(){
    Game();
    loadCharacter("characters.txt", _character_count);
    loadRiddle("riddles.txt", _riddle_count);
    loadEvent("random_events.txt", _event_count);
    
    for (int i = 0; i < _player_count; i++){
        cout << "Player " << i+1 << endl
        << "Choose a character: " << endl;
        
        for (int x = 0; x < _character_count; x++){
            string name = _characters[x].name;
            cout << "(" << x+1 << ") " << name << endl;
            // maybe add what stats each character has
        }

        int chosenCharacter;
        cout << "Enter your choice (1-" << _character_count << "): ";
        cin >> chosenCharacter;
        chosenCharacter--;
        for (int x = 0; x < 5; x++)
        {
            _board._players[i].setName(_characters[chosenCharacter].name);
            _board._players[i].setAge(_characters[chosenCharacter].age);
            _board._players[i].setStamina(_characters[chosenCharacter].stamina);
            _board._players[i].setStrength(_characters[chosenCharacter].strength);
            _board._players[i].setWisdom(_characters[chosenCharacter].wisdom);
            _board._players[i].setPridePoints(_characters[chosenCharacter].pridePoints);
        }
        int startingPath;
        cout << "Would you like to go to Cub Training (1) or Straight to the Pridelands (2)" << endl;
        cin >> startingPath;
        if (startingPath == 1){
            _board._players[i].trainCub();
            cout << "You have chosen to go through Cub Training, you gain 500 in all stats and a helpful advisor but lose 5000 pride points. " << endl;
            playAdvisor(i);
        }
        if (startingPath == 2){
            _board._players[i].toPrideLands();
            cout << "You have chosen to skip training and go straight to testing your skills in the Pridelands." << endl
            << "The road will be tougher but you have grown proud as a result, you gain only 200 points in all stats but gain 5000 pride points." << endl;
        }
    }
    _board.displayBoard();
    
}
