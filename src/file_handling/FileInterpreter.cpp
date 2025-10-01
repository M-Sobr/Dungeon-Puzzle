#include <exception>
#include <stdexcept>

#include "FileInterpreter.h"
#include "FileReader.h"
#include "qf_types/QFTypes.h"
#include "../effect/LevelUpEffects.h"
#include "../effect/Effect.h"
#include "../utils/ReadInput.h"
#include "../level/Tile.h"
#include "interpreting/MapInterpreter.h"
#include "interpreting/PlayerInterpreter.h"

#define SAVES_DIRECTORY_START "../../saves/"
#define CONFIG_DIRECTORY_START "../../config/"

#define MAP_LEVEL_DIRECTORY  "map_levels.txt"
#define PLAYER_LEVEL_DIRECTORY "player_levels.txt"

FileInterpreter::FileInterpreter(const std::string f_name) {
    this->exceptions = new FileInterpreterExceptionList(f_name);
}

void inline FileInterpreter::addException(FileInterpreterException* e) {
    *this->exceptions += e;
}

FileInterpreterExceptionList* FileInterpreter::getExceptionList() {
    return this->exceptions;
}

int FileInterpreter::loadMapLevels(std::vector<Level*>* levels) {
    try {
        // Intialise variables
        std::string path;
        path.append(CONFIG_DIRECTORY_START).append(MAP_LEVEL_DIRECTORY);

        // Run using map interpreter
        MapInterpreter mapInterpreter(MAP_LEVEL_DIRECTORY, path.c_str());
        return mapInterpreter.load(levels);
        
    
    } catch (FileInterpreterExceptionList* e) { 
        throw e;
    } catch (InvalidFileFormatException* e) {
        throw e;
    } catch (InvalidFileException* e) {
        throw e;
    }
} 

Effect* FileInterpreter::loadEffect(QFPair* effect_info) {
    // Value needs to be int
    try {
        QFInt* qf_int = effect_info->getValue()->get<QFInt>("Effect value is not QFInt!");
        std::string key = effect_info->getKey();

        return new Effect(key.c_str(), qf_int->getValue());
    
    } catch (NullPointerException* e) {
        throw e;
    } catch (InvalidEffectNameException* e) {
        throw new InvalidPlayerLevelException(e->what(), effect_info->getStartLine(), effect_info->getEndLine());
    }
}

EffectsList* FileInterpreter::loadEffectsList(QFDict* effects_list_info) {
    EffectsList* effects_list = new EffectsList();
    
    for (QFPair* qf_pair : effects_list_info->getPairs()) {
        try {
            effects_list->addEffect(this->loadEffect(qf_pair));
        } catch (FileInterpreterException* e) {
            this->addException(e);
        }
    }
    return effects_list;
}

EffectChoices* FileInterpreter::loadEffectChoices(QFList* effect_choices_list) {
    
    EffectChoices* effect_choices = new EffectChoices();

    for (QFValue* dict : effect_choices_list->getValues()) {
        try {
            effect_choices->addEffectList(this->loadEffectsList(dict->get<QFDict>("Effects list info is not QFDict!")));
        
        } catch (FileInterpreterException* e) {
            this->addException(e);
        }
    }
    return effect_choices;
}

void FileInterpreter::loadPlayerLevels(LevelUpEffects* level_up_effects) {
    try {
        // Intialise variables and read file
        std::string path;
        path.append(CONFIG_DIRECTORY_START).append(PLAYER_LEVEL_DIRECTORY);
        
        PlayerInterpreter playerInterpreter(PLAYER_LEVEL_DIRECTORY, path.c_str());
        return playerInterpreter.load(level_up_effects);

    } catch (FileInterpreterExceptionList* e) {
        throw e;
    } catch (InvalidFileException* e) {
        throw e;
    } catch (InvalidFileFormatException* e) {
        throw e;
    }
}

int inline FileInterpreter::resolveCorruptedSaveFile() {
    return ReadInput::getBinaryChoice("File data is corrupted!", "Exit Game", "Start New Game") - 2;
}

int FileInterpreter::loadSaveFile(const char* save_name) {
    printf("%s\n", save_name);
    
    QFDict level_file_contents(1);
    std::string path;
    path.append(SAVES_DIRECTORY_START).append(save_name);
    FileInterpreter fileInterpreter(save_name);
    
    try {
        FileReader level_file_reader(path.c_str());
        level_file_reader.readFile(&level_file_contents);
    
    } catch (InvalidFileFormatException*) {
        return resolveCorruptedSaveFile();
    
    } catch (InvalidFileException*) {
        std::string title;
        title.append("Create game with name ").append(title);
        return ReadInput::getBinaryChoice(title.c_str(), "Cancel", "Start New Game") - 2;
    }
    
    int choice = ReadInput::getBinaryChoice("Load save successful!", "Continue Game", "Start New Game");
    if (choice == 2) {
        return 0;
    }
    try {
        return level_file_contents.getValueFromKey("Current Level")->get<QFInt>("Value in Current Level is not QFInt!")->getValue() - 1;
   
    } catch (NoKeyFoundException*) {
        return resolveCorruptedSaveFile();
    
    } catch (NullPointerException*) {
        return resolveCorruptedSaveFile();
    }
}

void FileInterpreter::updateSaveFile(const char* save_name, int current_level) {
    std::string path;
    path.append(SAVES_DIRECTORY_START).append(save_name);
    std::ofstream output(path, std::ios::out | std::ios::trunc);
    if (output.is_open()) {
        output << "\"Current Level\": i" << current_level + 1;
        output.close();
    }
}

void FileInterpreter::deleteSaveFile(const char* save_name) {
    std::string path;
    path.append(SAVES_DIRECTORY_START).append(save_name);
    std::remove(path.c_str());
}