#include <exception>
#include <stdexcept>

#include "FileInterpreter.h"
#include "FileReader.h"
#include "qf_types/QFTypes.h"
#include "../effect/LevelUpEffects.h"
#include "../effect/Effect.h"
#include "../utils/ReadInput.h"
#include "../level/Tile.h"

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

LevelLayer FileInterpreter::loadMapLayer(QFList* layer_contents) {
    LevelLayer layer;
    std::string layer_string;

    // Create layer from strings
    for (QFValue* value : layer_contents->getValues()) {
        try {
            layer.addRow(value->get<QFString>("Row is empty or not QFString!")->getValue());
        
        } catch (NullPointerException* e) {
            this->addException(e);
        
        } catch (LevelBuilderException* e) {
            this->addException(new InvalidMapLevelException(e->what(), value->getStartLine(), value->getEndLine()));
        }
    }
    return layer;
}

void FileInterpreter::loadChests(QFDict* level_contents, Level::LevelBuilder* level_builder) {
    QFList* chests;
    try {
        chests = level_contents->getValueFromKey("Chests")->get<QFList>("");
    
    // Levels do not require a chests list (only if chests are in the level)
    } catch (FileInterpreterException* e) {
        return;
    } catch (NoKeyFoundException* e) {
        return;
    }

    QFDict* chest_contents;
    int chest_pos[3];
    bool valid_chest;
    for (QFValue* chest : chests->getValues()) {
        valid_chest = true;
        try {
            chest_contents = chest->get<QFDict>("Chest contents are not QFDict!");
        } catch (FileInterpreterException* e) {
            this->addException(e);
            continue;
        }

        // Get chest position
        QFList* chest_pos_list;
        try {
            chest_pos_list = chest_contents->getValueFromKey("Position")->get<QFList>("Chest position is empty or not QFList!");
        
        } catch (FileInterpreterException* e) {
            this->addException(e);
            
        } catch (NoKeyFoundException* e) {
            this->addException(new InvalidMapLevelException(e->what(), chest_contents->getStartLine(), chest_contents->getEndLine()));
        }

        std::vector<QFValue*> values = chest_pos_list->getValues();

        if (values.size() != 3) {
            this->addException(new InvalidMapLevelException("Chest position needs three values!", 
                chest_pos_list->getStartLine(), chest_pos_list->getEndLine()));
        
        } else {
            for (int i=0; i<3; i++) {
                try {
                    chest_pos[i] = values.at(i)->get<QFInt>("Chest position values must be QFInt!")->getValue();
                } catch (FileInterpreterException* e) {
                    this->addException(e);
                } 
            }
        }
    }
}

Level* FileInterpreter::loadMapLevel(QFDict* level_contents) {
    // Initialisation of variables
    std::string level_string;
    Level::LevelBuilder level_builder = Level::LevelBuilder();

    // Get level name 
    try {
        std::string level_name = level_contents->getValueFromKey("Level Name")->get<QFString>("Level name is empty or not QFString!")->getValue();
        level_builder.setName(level_name);
    
    } catch (FileInterpreterException* e) {
        this->addException(e);
    
    } catch (NoKeyFoundException* e) {
        this->addException(new InvalidMapLevelException(e->what(), level_contents->getStartLine(), level_contents->getEndLine()));
    }

    // Get level layout
    QFList* layout;
    try {
        layout = level_contents->getValueFromKey("Layout")->get<QFList>("Layout is empty or not QFList!");
    
    } catch (FileInterpreterException* e) {
        throw e;
    
    } catch (NoKeyFoundException* e) {
        throw new InvalidMapLevelException(e->what(), 
            level_contents->getStartLine(), level_contents->getEndLine());
    }

    for (QFValue* layer : layout->getValues()) {
        try {
            level_builder.addLayer(this->loadMapLayer(layer->get<QFList>("Layer contents are empty or not QFList!")));
        } catch (FileInterpreterException* e) {
            this->addException(e);
        }
    }

    // Add chests
    this->loadChests(level_contents, &level_builder);

    // Build the level
    try {
        return level_builder.build();
    } catch (LevelBuilderException* e) {
        throw new InvalidMapLevelException(e->what(), level_contents->getStartLine(), level_contents->getEndLine());
    }
}

int FileInterpreter::loadMapLevels(std::vector<Level*>* levels) {
    try {
        // Intialise variables
        std::string path;
        path.append(CONFIG_DIRECTORY_START).append(MAP_LEVEL_DIRECTORY);
        FileReader level_file_reader(path.c_str());
        QFDict level_file_contents(1);
        QFList* map_levels_list;
        FileInterpreter fileInterpreter(MAP_LEVEL_DIRECTORY);

        // Read File
        level_file_reader.readFile(&level_file_contents);

        // Get list of map levels
        try {
            map_levels_list = level_file_contents.getValueFromKey("Map Levels")->get<QFList>("No QFList in a \"Map Levels\" key found.");
        
        } catch (FileInterpreterException* e) {
            fileInterpreter.addException(e);
            throw fileInterpreter.getExceptionList();
        
        } catch (NoKeyFoundException* e) {
            fileInterpreter.addException(new InvalidMapLevelException(e->what(), 
                level_file_contents.getStartLine(), level_file_contents.getEndLine()));
            throw fileInterpreter.getExceptionList(); 
        }

        std::vector<QFValue*> map_level_values = map_levels_list->getValues();

        for (QFValue* dict : map_level_values) {
            try {
                levels->push_back(fileInterpreter.loadMapLevel(dict->get<QFDict>("Entry in Map Levels list is not QFDict!")));
            } catch (FileInterpreterException* e) {
                fileInterpreter.addException(e);
            }
        }
        
        FileInterpreterExceptionList* exceptionList = fileInterpreter.getExceptionList();
        if (exceptionList->size() > 0) {
            throw exceptionList;
        }

        return (int)levels->size();
    
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
        FileReader level_file_reader(path.c_str());
        QFDict level_file_contents(1);
        level_file_reader.readFile(&level_file_contents);
        FileInterpreter fileInterpreter("player_levels.txt");

        // Get dict of player levels
        QFDict* player_levels_dict;
        try {
            player_levels_dict = level_file_contents.getValueFromKey("Player Levels")->
                get<QFDict>("No QFDict in a \"Player Levels\" key found.");
        
        } catch (FileInterpreterException* e) {
            fileInterpreter.addException(e);
            throw fileInterpreter.getExceptionList();
        
        } catch (NoKeyFoundException* e) {
            fileInterpreter.addException(new InvalidMapLevelException(e->what(), 
                level_file_contents.getStartLine(), level_file_contents.getEndLine()));
            throw fileInterpreter.getExceptionList();
        }

        // Get list of player level effects
        QFList* player_effects_list;
        try {
            player_effects_list = player_levels_dict->getValueFromKey("Effects")->
                get<QFList>("No QFList in a \"Effects\" key found.");
        
        } catch (FileInterpreterException* e) {
            fileInterpreter.addException(e);
            throw fileInterpreter.getExceptionList();
        
        } catch (NoKeyFoundException* e) {
            fileInterpreter.addException(new InvalidMapLevelException(e->what(), 
                player_levels_dict->getStartLine(), player_levels_dict->getEndLine()));
            throw fileInterpreter.getExceptionList();     
        }


        *level_up_effects = LevelUpEffects::LevelUpEffects();

        for (QFValue* list : player_effects_list->getValues()) {
            try {
                level_up_effects->addLevel(fileInterpreter.loadEffectChoices(list->get<QFList>("Player level effects list is not QFList!")));
            } catch (FileInterpreterException* e) {
                fileInterpreter.addException(e);
            }
        }

        FileInterpreterExceptionList* exceptionList = fileInterpreter.getExceptionList();
        if (exceptionList->size() > 0) {
            throw exceptionList;
        }

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