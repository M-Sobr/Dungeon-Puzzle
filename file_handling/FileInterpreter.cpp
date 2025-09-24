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
    LevelLayer layer;
    if (layer_contents == nullptr) {
        throw new InvalidMapLevelException("Layer contents are empty or not QFList!");
    }
    
    // Create layer from strings
    std::string layer_string;
    for (QFValue* value : layer_contents->getValues()) {
        try {
            layer_string = dynamic_cast<QFString*>(value)->getValue();
        } catch (NullPointerException* e) {
            delete e;
            throw new InvalidMapLevelException("Row is empty or not QFString!");
        }
        layer.addRow(layer_string);
    }
    return layer;
}

Level* FileInterpreter::loadMapLevel(QFDict* level_contents) {
    // Check if level_contents is null
    if (level_contents == nullptr) {
        throw new InvalidMapLevelException("Level contents is empty or not QFDict!");
    }
    
    // Initialisation of variables
    std::string level_name;
    std::string level_string;
    Level::LevelBuilder level_builder = Level::LevelBuilder();

    // Get level name
    try {    
        level_name = dynamic_cast<QFString*>(level_contents->getValueFromKey("Level Name"))->getValue();
    } catch (NullPointerException* e) {
        delete e;
        throw new InvalidMapLevelException("Level name is empty or not QFString!");
    }    
    level_builder.setName(level_name);

    // Get level layout
    QFList* layout;
    try {
        layout = dynamic_cast<QFList*>(level_contents->getValueFromKey("Layout"));
    } catch (NullPointerException* e) {
        delete e;
        throw new InvalidMapLevelException("Layout is empty or not QFList!");
    }
    
    try {
        for (QFValue* layer : layout->getValues()) {
            level_builder.addLayer(loadMapLayer(dynamic_cast<QFList*>(layer)));
        }
    } catch (InvalidMapLevelException* e) {
        throw e;
    }

    //new Level(char level_name[MAX_LEVEL_NAME_LENGTH], char level_string[MAX_LEVEL_CHARACTERS], int level_rows, int level_cols);
    return level_builder.build();;
}

int FileInterpreter::loadMapLevels(std::vector<Level*>* levels) {
    
    // Intialise variables and read file
    FileReader level_file_reader(MAP_LEVEL_DIRECTORY);
    QFDict level_file_contents;
    try {
        level_file_reader.readFile(&level_file_contents);
    } catch (InvalidFileException* e) {
        throw e;
    }

    // Get list of map levels
    QFList* map_levels_list;
    try {
        map_levels_list = dynamic_cast<QFList*>(level_file_contents.getValueFromKey("Map Levels"));
    } catch (NullPointerException* e) {
        delete e;
        throw new InvalidFileFormatException("No QFList in a \"Map Levels\" key found.");
    }

    std::vector<QFValue*> map_level_values = map_levels_list->getValues();

    try {
        for (QFValue* dict : map_level_values) {
            levels->push_back(loadMapLevel(dynamic_cast<QFDict*>(dict)));
        }
    } catch (InvalidMapLevelException* e) {
        throw e;
    }

    return (int)levels->size();
} 

Effect* FileInterpreter::loadEffect(QFPair* effect_info) {
    if (effect_info == nullptr) {
        throw new InvalidPlayerLevelException("Effect info is not QFPair!");
    }

    // Value needs to be int
    QFInt* value = dynamic_cast<QFInt*>(effect_info->getValue());
    if (value == nullptr) {
        throw new InvalidPlayerLevelException("Effect value is not QFInt!");
    }

    std::string key = effect_info->getKey();
    if (key == "GAIN_MAX_HEALTH") {
        return new Effect(EffectTypes::GAIN_MAX_HEALTH, value->getValue());
    
    } else if (key == "GAIN_HEALTH") {
        return new Effect(EffectTypes::GAIN_HEALTH, value->getValue());
    
    } else if (key == "GAIN_EXPERIENCE") {
        return new Effect(EffectTypes::GAIN_EXPERIENCE, value->getValue());
    
    } else if (key == "TAKE_DAMAGE") {
        return new Effect(EffectTypes::TAKE_DAMAGE, value->getValue());
    
    }
    throw new InvalidPlayerLevelException("Effect key is not a valid effect name!");

}

EffectsList* FileInterpreter::loadEffectsList(QFDict* effects_list_info) {
    if (effects_list_info == nullptr) {
        throw new InvalidPlayerLevelException("Effects list info is not QFDict!");
    }

    EffectsList* effects_list = new EffectsList();
    try {
        for (QFPair* qf_pair : effects_list_info->getPairs()) {
            effects_list->addEffect(loadEffect(qf_pair));
        }

    } catch(InvalidPlayerLevelException* e) {
        throw e;
    }
    return effects_list;
}

std::vector<EffectsList*> FileInterpreter::loadPlayerLevel(QFList* level_effects_list) {
    // Check if level_effects_list is null
    if (level_effects_list == nullptr) {
        throw new InvalidPlayerLevelException("Player level effects list is not QFList!");
    }

    std::vector<EffectsList*> effects_list;

    try {
        for (QFValue* value : level_effects_list->getValues()) {
            effects_list.push_back(loadEffectsList(dynamic_cast<QFDict*>(value)));
        }

    } catch(InvalidPlayerLevelException* e) {
        throw e;
    }
    return effects_list;
}

void FileInterpreter::loadPlayerLevels(LevelUpEffects* level_up_effects) {
    
    // Intialise variables and read file
    FileReader level_file_reader(PLAYER_LEVEL_DIRECTORY);
    QFDict level_file_contents;
    try {
        level_file_reader.readFile(&level_file_contents);
    } catch (InvalidFileException* e) {
        throw e;
    }

    // Get dict of player levels
    QFDict* player_levels_dict = dynamic_cast<QFDict*>(level_file_contents.getValueFromKey("Player Levels"));
    if (player_levels_dict == nullptr) {
        throw new InvalidFileFormatException("No QFDict in a \"Player Levels\" key found.");
    }

    // Get list of player level effects
    QFList* player_effects_list = dynamic_cast<QFList*>(player_levels_dict->getValueFromKey("Effects"));
    if (player_effects_list == nullptr) {
        throw new InvalidFileFormatException("No QFDict in a \"Player Levels\" key found.");
    }

    *level_up_effects = LevelUpEffects::LevelUpEffects();

    try {
        for (QFValue* list : player_effects_list->getValues()) {
            level_up_effects->addLevel(loadPlayerLevel(dynamic_cast<QFList*>(list)));
        }
    } catch (InvalidPlayerLevelException* e) {
        throw e;
    }


}