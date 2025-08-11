#include "level/Level.h"
#include "player/Player.h"

#include <iostream>
#include <string>

#define LEVEL_COUNT 10

void playLevel(Level level) {
    bool level_ongoing = true;
    Player player = Player::Player("Player");
    while (level_ongoing) {
        // Print level details
        level.printName();
        level.printLevel();
        
        // Print Player Details
        player.printDetails();

        bool input_required = true;
        while (input_required) {
            // Get input from player
            std::cout << "Action: ";
            char s[100];
            std::cin >> s;
        
            // Temporary code to escape loop for testing
            if (s[0] == 'E' && s[1] == 'X' && s[2] == 'I' && s[3] == 'T') {
                return;
            }
        }
        
    }

}


int main(void) {
    Level levels[LEVEL_COUNT];
    int levelQuantity = loadLevels(levels);
    int currentLevelIndex = 0;
    
    // Play levels
    while (currentLevelIndex < levelQuantity) {
        playLevel(levels[currentLevelIndex]);
        currentLevelIndex ++;
    }
}