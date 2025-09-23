#include <exception>
#include <stdexcept>

#include "FileInterpreter.h"
#include "FileReader.h"
#include "../level/Level.h"
#include "qf_types/QFTypes.h"
#include "FileExceptions.h"

#define MAP_LEVEL_DIRECTORY  "config/map_levels.txt"

LevelLayer FileInterpreter::loadLayer(QFList* layer_contents) {
    LevelLayer layer;
    if (layer_contents == nullptr) {
        throw new InvalidLevelException("Layer contents are empty or not QFList!");
    }
    
    // Create layer from strings
    std::string layer_string;
    for (QFValue* value : layer_contents->getValues()) {
        layer_string = dynamic_cast<QFString*>(value)->getValue();
        if (layer_string == "") {
            throw new InvalidLevelException("Row is empty or not QFString!");
        }
        layer.addRow(layer_string);
    }
    return layer;
}

Level* FileInterpreter::loadLevel(QFDict* level_contents) {
    // Check if level_contents is null
    if (level_contents == nullptr) {
        throw new InvalidLevelException("Level contents is empty or not QFDict!");
    }
    
    // Initialisation of variables
    std::string level_name;
    std::string level_string;
    Level::LevelBuilder level_builder = Level::LevelBuilder();

    // Get level name
    level_name = dynamic_cast<QFString*>(level_contents->getValueFromKey("Level Name"))->getValue();
    if (level_name == "") {
        throw new InvalidLevelException("Level name is empty or not QFString!");
    }
    level_builder.setName(level_name);

    // Get level layout
    QFList* layout = dynamic_cast<QFList*>(level_contents->getValueFromKey("Layout"));
    if (layout == nullptr) {
        throw new InvalidLevelException("Layout is empty or not QFList!");
    }
    
    try {
        for (QFValue* layer : layout->getValues()) {
            level_builder.addLayer(loadLayer(dynamic_cast<QFList*>(layer)));
        }
    } catch (InvalidLevelException* e) {
        throw e;
    }

    //new Level(char level_name[MAX_LEVEL_NAME_LENGTH], char level_string[MAX_LEVEL_CHARACTERS], int level_rows, int level_cols);
    return level_builder.build();;
}

int FileInterpreter::loadLevels(std::vector<Level*>* levels) {
    
    // Intialise variables and read file
    FileReader level_file_reader(MAP_LEVEL_DIRECTORY);
    QFDict level_file_contents;
    try {
        level_file_reader.readFile(&level_file_contents);
    } catch (InvalidFileException* e) {
        throw e;
    }

    QFList* map_levels_list = dynamic_cast<QFList*>(level_file_contents.getValueFromKey("Map Levels"));
    if (map_levels_list == nullptr) {
        throw new InvalidFileFormatException("No QFList in a \"Map Levels\" key found.");
    }

    std::vector<QFValue*> map_level_values = map_levels_list->getValues();
    std::set<int> filled_levels;

    try {
        for (QFValue* dict : map_level_values) {
            levels->push_back(loadLevel(dynamic_cast<QFDict*>(dict)));
        }
    } catch (InvalidLevelException* e) {
        throw e;
    }

    return (int)levels->size();
} 