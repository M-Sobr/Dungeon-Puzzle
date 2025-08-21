#include "level/Level.h"
#include "player/Player.h"
#include "player/Action.h"

#include <iostream>
#include <string>

#define LEVEL_COUNT 10
#define START_LEVEL 2  // Temporary while saves are not implemented

bool playLevel(Level* level) {
    bool level_ongoing = true;
    Player player = Player::Player("Player");
    while (level_ongoing) {
        // Print level details
        level->printName();
        level->printLevel();
        
        // Print Player Details
        player.printDetails();

        while (true) {
            // Get input from player
            std::cout << "Action: ";
            char s[100];
            std::cin >> s;
            
            Action action = Action::fromText(s);
            if (action.getType() == ActionType::EXIT) {
                return false;
            }
            if (action.getType() != ActionType::NULL_ACTION) {
                action.resolveAction(level, &player);
                break;
            }
        }
        if (!player.isAlive()) {
            std::cout << "The player is dead!" << "\n\n";
            return false;
        }
        if (level->isBeaten()) {
            std::cout << "The level has been beaten!" << "\n\n";
            return true;
        }
    }
    return true;
}


int main(void) {
    Level levels[LEVEL_COUNT];
    int levelQuantity = loadLevels(levels);
    int currentLevelIndex = START_LEVEL - 1;
    
    // Play levels
    while (currentLevelIndex < levelQuantity) {
        if (!playLevel(&levels[currentLevelIndex])) {
            break;
        }
        currentLevelIndex ++;
    }
}