#include <exception>
#include <stdexcept>

#include "FileInterpreter.h"
#include "FileReader.h"
#include "../level/Level.h"
#include "qf_types/QFTypes.h"
#include "../effect/LevelUpEffects.h"
#include "../effect/Effect.h"

#define MAP_LEVEL_DIRECTORY  "config/map_levels.txt"
#define PLAYER_LEVEL_DIRECTORY "config/player_levels.txt"

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
        }    
    }
    return layer;
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
    try {
        return level_builder.build();
    } catch (LevelBuilderException* e) {
        throw new InvalidMapLevelException(e->what(), level_contents->getStartLine(), level_contents->getEndLine());
    }
}

int FileInterpreter::loadMapLevels(std::vector<Level*>* levels) {
    try {
        // Intialise variables
        FileReader level_file_reader(MAP_LEVEL_DIRECTORY);
        QFDict level_file_contents(1);
        QFList* map_levels_list;
        FileInterpreter fileInterpreter("map_levels.txt");

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

std::vector<EffectsList*> FileInterpreter::loadPlayerLevel(QFList* level_effects_list) {
    
    std::vector<EffectsList*> effects_list;

    for (QFValue* dict : level_effects_list->getValues()) {
        try {
            effects_list.push_back(this->loadEffectsList(dict->get<QFDict>("Effects list info is not QFDict!")));
        
        } catch (FileInterpreterException* e) {
            this->addException(e);
        }
    }
    return effects_list;
}

void FileInterpreter::loadPlayerLevels(LevelUpEffects* level_up_effects) {
    try {
        // Intialise variables and read file
        FileReader level_file_reader(PLAYER_LEVEL_DIRECTORY);
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
                level_up_effects->addLevel(fileInterpreter.loadPlayerLevel(list->get<QFList>("Player level effects list is not QFList!")));
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