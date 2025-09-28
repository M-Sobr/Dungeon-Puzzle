#include "level/Level.h"
#include "player/Player.h"
#include "player/Action.h"
#include "player/PastAction.h"
#include "file_handling/FileInterpreter.h"
#include "file_handling/FileExceptions.h"
#include "effect/LevelUpEffects.h"
#include "utils/ReadInput.h"
#include "utils/Utils.h"

#include <iostream>
#include <string>

// Global variables
LevelUpEffects level_up_effects;

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
            Action action = Action::fromText(ReadInput::getUserInput("Action: ").c_str());
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
        levelQuantity = FileInterpreter::loadMapLevels(&levels);
    
    } catch (InvalidFileException* e) {
        printf("%s\n", e->what());
    
    } catch (InvalidFileFormatException* e) {
        printf("%s\n",e->what());
    
    } catch (FileInterpreterExceptionList* e) {
        printf("%s\n", e->what());
    } 
    
    
    try {
        FileInterpreter::loadPlayerLevels(&level_up_effects);
    
    } catch (InvalidFileException* e) {
        printf("%s\n", e->what());
    
    } catch (InvalidFileFormatException* e) {
        printf("%s\n",e->what());
    
    } catch (FileInterpreterExceptionList* e) {
        printf("%s\n", e->what());
    } 

    if (levelQuantity < 1) {
        return 0;
    }

    // Get save details from player
    std::string save_name;
    int currentLevelIndex = -1;
    while (currentLevelIndex == -1) {
        save_name = ReadInput::getUserInput("Save Name: ");
        if (equalsIgnoreCase(save_name.c_str(), "exit", 4)) {
            return 0;
        }
        currentLevelIndex = FileInterpreter::loadSaveFile(save_name.c_str());
    }

    // Play levels
    while (currentLevelIndex < levelQuantity) {
        switch (playLevel(*(levels.at(currentLevelIndex)))) {
            case LevelFinishResult::LEVEL_EXIT:
                return 0;
            case LevelFinishResult::LEVEL_VICTORY:
                currentLevelIndex ++;
                FileInterpreter::updateSaveFile(save_name.c_str(), currentLevelIndex);
        }   
    }
    printf("You have beaten the game!");
    FileInterpreter::deleteSaveFile(save_name.c_str());
}