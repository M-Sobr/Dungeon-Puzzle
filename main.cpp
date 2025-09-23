#include "level/Level.h"
#include "player/Player.h"
#include "player/Action.h"
#include "player/PastAction.h"
#include "file_handling/FileInterpreter.h"
#include "file_handling/FileExceptions.h"

#include <iostream>
#include <string>

#define LEVEL_COUNT 10
#define START_LEVEL 1  // Temporary while saves are not implemented

enum LevelFinishResult {
    LEVEL_VICTORY,
    LEVEL_RESET,
    LEVEL_EXIT
};

LevelFinishResult playLevel(Level level) {
    bool level_ongoing = true;
    Player player = Player::Player("Player");
    std::vector<PastAction*> previousActions;
    while (level_ongoing) {
        // Print level details
        level.printName();
        level.printLevel();
        
        // Print Player Details
        player.printDetails();

        while (true) {
            // Get input from player
            std::cout << "Action: ";
            char s[100];
            std::cin >> s;
            
            Action action = Action::fromText(s);
            switch (action.getType()) {
                case ActionType::EXIT:
                    return LevelFinishResult::LEVEL_EXIT;
                case ActionType::RESET:
                    return LevelFinishResult::LEVEL_RESET;
            }   
            if ((action.getType() == ActionType::UNDO) && (previousActions.size() == 0)) {
                continue; 

            } else if ((action.getType() == ActionType::UNDO)) {
                PastAction* past_action = previousActions.back();
                previousActions.pop_back();
                past_action->undoAction(&level, &player);
                delete past_action;
                break;
            
            } else if (action.getType() != ActionType::NULL_ACTION) {
                previousActions.push_back(action.resolveAction(&level, &player));
                break;
            }
        }
        if (!player.isAlive()) {
            std::cout << "The player is dead!" << "\n\n";
            return LevelFinishResult::LEVEL_RESET;
        }
        if (level.isBeaten()) {
            std::cout << "The level has been beaten!" << "\n\n";
            return LevelFinishResult::LEVEL_VICTORY;
        }
    }
    return LevelFinishResult::LEVEL_VICTORY;
}


int main(void) {
    std::vector<Level*> levels;
    int levelQuantity = 0;
    try {
        levelQuantity = FileInterpreter::loadLevels(&levels);
    } catch (InvalidFileException* e) {
        printf("%s\n", e->what());
    
    } catch (InvalidFileFormatException* e) {
        printf("%s\n",e->what());
    }
    int currentLevelIndex = START_LEVEL - 1;

    // Play levels
    while (currentLevelIndex < levelQuantity) {
        switch (playLevel(*(levels.at(currentLevelIndex)))) {
            case LevelFinishResult::LEVEL_EXIT:
                currentLevelIndex = levelQuantity;
                break;
            case LevelFinishResult::LEVEL_VICTORY:
                currentLevelIndex ++;
        }   
    }
}