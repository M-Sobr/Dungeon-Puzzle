#include <exception>
#include <stdexcept>

#include "FileInterpreter.h"
#include "FileReader.h"
#include "../level/Level.h"
#include "qf_types/QFTypes.h"
#include "FileExceptions.h"
#include "../effect/LevelUpEffects.h"
#include "../effect/Effect.h"

#define MAP_LEVEL_DIRECTORY  "config/map_levels.txt"
#define PLAYER_LEVEL_DIRECTORY "config/player_levels.txt"

LevelLayer FileInterpreter::loadMapLayer(QFList* layer_contents) {
    try {
        LevelLayer layer;
        std::string layer_string;

        // Create layer from strings
        for (QFValue* value : layer_contents->getValues()) {
            layer.addRow(value->get<QFString>("Row is empty or not QFString!")->getValue());
        }
        return layer;
    } catch (NullPointerException* e) {
        throw e;
    }
}

Level* FileInterpreter::loadMapLevel(QFDict* level_contents) {
    try {
        // Initialisation of variables
        std::string level_string;
        Level::LevelBuilder level_builder = Level::LevelBuilder();

        // Get level name 
        std::string level_name = level_contents->getValueFromKey("Level Name")->get<QFString>("Level name is empty or not QFString!")->getValue();
        level_builder.setName(level_name);

        // Get level layout
        QFList* layout = level_contents->getValueFromKey("Layout")->get<QFList>("Layout is empty or not QFList!");
        
        for (QFValue* layer : layout->getValues()) {
            level_builder.addLayer(loadMapLayer(layer->get<QFList>("Layer contents are empty or not QFList!")));
        }
        return level_builder.build();;

    } catch (InvalidMapLevelException* e) {
        throw e;
    
    } catch (NullPointerException* e) {
        throw e;
    }
}

int FileInterpreter::loadMapLevels(std::vector<Level*>* levels) {
    try {
        // Intialise variables
        FileReader level_file_reader(MAP_LEVEL_DIRECTORY);
        QFDict level_file_contents(1);
        QFList* map_levels_list;
        
        // Read File
        level_file_reader.readFile(&level_file_contents);

        // Get list of map levels
        map_levels_list = level_file_contents.getValueFromKey("Map Levels")->get<QFList>("No QFList in a \"Map Levels\" key found.");
        
        std::vector<QFValue*> map_level_values = map_levels_list->getValues();

        for (QFValue* dict : map_level_values) {
            levels->push_back(loadMapLevel(dict->get<QFDict>("Entry in Map Levels list is not QFDict!")));
        }

        return (int)levels->size();
    
    } catch (InvalidFileException* e) { 
        throw e;
    } catch (InvalidMapLevelException* e) {
        throw e;
    } catch (NullPointerException* e) {
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
        throw new InvalidPlayerLevelException(e->what());
    }
}

EffectsList* FileInterpreter::loadEffectsList(QFDict* effects_list_info) {
    try {

        EffectsList* effects_list = new EffectsList();
       
        for (QFPair* qf_pair : effects_list_info->getPairs()) {
            effects_list->addEffect(loadEffect(qf_pair));
        }
        return effects_list;

    } catch(InvalidPlayerLevelException* e) {
        throw e;
    } catch(NullPointerException* e) {
        throw e;
    }
}

std::vector<EffectsList*> FileInterpreter::loadPlayerLevel(QFList* level_effects_list) {
    try {
        std::vector<EffectsList*> effects_list;

        for (QFValue* dict : level_effects_list->getValues()) {
            effects_list.push_back(loadEffectsList(dict->get<QFDict>("Effects list info is not QFDict!")));
        }
        return effects_list;
    
    } catch(InvalidPlayerLevelException* e) {
        throw e;
    } catch(NullPointerException* e) {
        throw e;
    }
}

void FileInterpreter::loadPlayerLevels(LevelUpEffects* level_up_effects) {
    try {
        // Intialise variables and read file
        FileReader level_file_reader(PLAYER_LEVEL_DIRECTORY);
        QFDict level_file_contents(1);
        level_file_reader.readFile(&level_file_contents);

        // Get dict of player levels
        QFDict* player_levels_dict = level_file_contents.getValueFromKey("Player Levels")->
            get<QFDict>("No QFDict in a \"Player Levels\" key found.");

        // Get list of player level effects
        QFList* player_effects_list = player_levels_dict->getValueFromKey("Effects")->
            get<QFList>("No QFList in a \"Effects\" key found.");

        *level_up_effects = LevelUpEffects::LevelUpEffects();

        for (QFValue* list : player_effects_list->getValues()) {
            level_up_effects->addLevel(loadPlayerLevel(list->get<QFList>("Player level effects list is not QFList!")));
        }

    } catch (InvalidPlayerLevelException* e) {
        throw e;
    } catch (InvalidFileException* e) {
        throw e;
    } catch (NullPointerException* e) {
        throw e;
    }
}