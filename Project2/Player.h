#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
using namespace std;

class Player
{
    private:
        string _name;
        int _strength;
        int _stamina; 
        int _wisdom;
        int _pride_points;
        int _age;
        int _advisor;
        int _starting_path;

    public:
        
        Player();
        Player(string name, int age, int strength, int stamina, int wisdom, int pridePoints);
        string getName();
        int getStrength();
        int getStamina(); 
        int getWisdom();
        int getPridePoints();
        int getAge();
        int getPlayerIndex();
        int getAdvisor();
        int getStartingPath();
        
        void setStartingPath(int path);
        void setAdvisor(int advisor);
        void setName(string name);
        void setStrength(int strength);
        void setStamina(int stamina); 
        void setWisdom(int wisdom);
        void setPridePoints(int pridePoints);
        void setAge(int age);
        
        void modifyStrength(int strength);
        void modifyStamina(int stamina); 
        void modifyWisdom(int wisdom);
        void modifyPridePoints(int pridePoints);
        void modifyAge(int age);


        void trainCub();
        void toPrideLands();
        void printStats();
};
#endif