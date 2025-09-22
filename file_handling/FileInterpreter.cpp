#include <exception>
#include <stdexcept>

#include "FileInterpreter.h"
#include "FileReader.h"
#include "../level/Level.h"
#include "qf_types/QFTypes.h"

#define MAP_LEVEL_DIRECTORY  "config/map_levels.txt"

Level* FileInterpreter::loadLevel(QFDict* level_contents) {
    // Initialisation of variables
    std::string level_name;
    std::string level_string;
    int level_rows;
    int level_cols;

    // Get level name
    level_name = dynamic_cast<QFString*>(level_contents->getValueFromKey("Level Name"))->getValue();
    if (level_name == "") {
        return new Level();
    }

    // Get level layout
    QFList* layout = dynamic_cast<QFList*>(level_contents->getValueFromKey("Layout"));
    if (layout == nullptr) {
        return new Level();
    } 

    printf("Success3\n");

    //new Level(char level_name[MAX_LEVEL_NAME_LENGTH], char level_string[MAX_LEVEL_CHARACTERS], int level_rows, int level_cols);
    return new Level();
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