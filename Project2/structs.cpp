#include <iostream>
#include "Player.h"
#include "Tile.h"
#include "Board.h"
#include "Game.h"
#include <fstream>
#ifndef STRUCTS_H
#define STRUCTS_H
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
struct Character
{
    string name;
    int age;
    int stamina;
    int strength;
    int wisdom;
    int pridePoints;
};

void loadCharacter(string filename, Character characters[], const int arr_size){
    ifstream infile(filename);
    string line;
    if (infile.is_open()){
        return; // if file fails to open stop the function
    }

    getline(infile, line); // read the header line
    

    string stats[6];
    while (getline(infile, line)){
        split(line, '|', stats, 6);
        for (int i = 0; i < arr_size; i++){
            characters[i].name = stats[0];
            characters[i].age = stoi(stats[1]);
            characters[i].stamina = stoi(stats[2]);
            characters[i].strength = stoi(stats[3]);
            characters[i].wisdom = stoi(stats[4]);
            characters[i].pridePoints = stoi(stats[5]);
        }
    }
}



struct Riddle
{
    string question;
    string answer;
};
void loadRiddle(string filename, Riddle riddles[], const int arr_size)
{
    ifstream infile(filename);
    string line;
    if (infile.is_open()){
        return; // if file fails to open stop the function
    }

    getline(infile, line); // read the header line

    string arr[2];
    while (getline(infile, line)){
        split(line, '|', arr, 2);
        for (int i = 0; i < arr_size; i++){
            riddles[i].question = arr[0];
            riddles[i].answer = arr[1];
        }
    }
}

Player playRiddle(Player p, Riddle riddles[], const int riddle_count)
{
    int selected_index = rand() % (riddle_count-1);
    string question = riddles[selected_index].question;
    string answer = riddles[selected_index].answer;
    cout << question << endl; 

    string input;
    getline(cin, input); // read user's answer 
    if (input == answer){
        p.modifyWisdom(500); //increase wisdom 500
        cout << "Correct! A smart answer grants you +500 wisdom." << endl;
    }
    else {
        cout << "Unfortunately that is incorrect. More Challenges await you in the future." << endl;
    }

    return p;
}
#endif