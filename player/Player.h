#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

class Player {
    private:
        std::string name;
        int level;
        int health;
        int max_health;
        int movement;
        int currentXp;
        int xpRequired;
    
    public:
        Player(std::string input_name);
        void printDetails();
        int getMovement();
        void takeDamage(int damage);
        void gainExperience(int experience);
        void heal();
};

#endif