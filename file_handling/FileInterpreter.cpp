#include <exception>
#include <stdexcept>

#include "FileInterpreter.h"
#include "FileReader.h"
#include "../level/Level.h"
#include "qf_types/QFTypes.h"

#define MAP_LEVEL_DIRECTORY  "config/map_levels.txt"

LevelLayer FileInterpreter::loadLayer(QFList* layer_contents, bool* success) {
    LevelLayer layer;
    if (layer_contents == nullptr) {
        *success = 0;
        return layer;
    }
    printf("Success4\n");
    
    // Create layer from strings
    std::string layer_string;
    for (QFValue* value : layer_contents->getValues()) {
        printf("a");
        layer_string = dynamic_cast<QFString*>(value)->getValue();
        if (layer_string == "") {
            *success = 0;
            return layer;
        }
        layer.addRow(layer_string);
    }
    printf("Sucess5\n");
    return layer;
}

Level* FileInterpreter::loadLevel(QFDict* level_contents) {
    // Initialisation of variables
    std::string level_name;
    std::string level_string;
    int level_rows;
    int level_cols;
    Level::LevelBuilder level_builder = Level::LevelBuilder();

    // Get level name
    level_name = dynamic_cast<QFString*>(level_contents->getValueFromKey("Level Name"))->getValue();
    if (level_name == "") {
        return nullptr;
    }
    level_builder.setName(level_name);

    // Get level layout
    QFList* layout = dynamic_cast<QFList*>(level_contents->getValueFromKey("Layout"));
    if (layout == nullptr) {
        return nullptr;
    }
    bool layer_add_success = 1;
    for (QFValue* layer : layout->getValues()) {
        level_builder.addLayer(loadLayer(dynamic_cast<QFList*>(layer), &layer_add_success));
    }
    if (!layer_add_success) {
        return nullptr;
    }
    level_builder.build();

    //new Level(char level_name[MAX_LEVEL_NAME_LENGTH], char level_string[MAX_LEVEL_CHARACTERS], int level_rows, int level_cols);
    return level_builder.build();;
}

int FileInterpreter::countLevels(Level* levels, std::set<int> filled_levels) {
    int count = 0;
    while (filled_levels.count(count)) {
        count ++;
    }
    return count;
}

int FileInterpreter::loadLevels(std::vector<Level*> levels) {
    
    // Intialise variables and read file
    FileReader level_file_reader(MAP_LEVEL_DIRECTORY);
    QFDict level_file_contents;
    
    FileReaderErrorCode errorCode = level_file_reader.readFile(&level_file_contents);
    switch (errorCode) {
        case FileReaderErrorCode::INVALID_FILE:
            printf("Invalid file!\n");    
            return 0;
            case FileReaderErrorCode::INVALID_FILE_FORMAT:
            printf("Invalid file format!\n");    
            return 0;    
    }

    QFList* map_levels_list = dynamic_cast<QFList*>(level_file_contents.getValueFromKey("Map Levels"));
    if (map_levels_list == nullptr) {
        printf("%s", "No QFList in a \"Map Levels\" key found\n");
        return 0;
    }

    printf("Success1!\n");

    std::vector<QFValue*> map_level_values = map_levels_list->getValues();
    std::set<int> filled_levels;

    for (QFValue* dict : map_level_values) {
        levels.push_back(loadLevel(dynamic_cast<QFDict*>(dict)));
    }

    printf("Success2!\n");

    return (int)levels.size();
} 