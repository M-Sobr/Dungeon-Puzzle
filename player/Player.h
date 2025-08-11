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
    
    public:
        Player(std::string input_name);
        void printDetails();
};

#endif