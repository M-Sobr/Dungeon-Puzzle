#include <exception>
#include <stdexcept>

#include "FileInterpreter.h"
#include "FileReader.h"
#include "../level/Level.h"
#include "qf_types/QFTypes.h"

#define MAP_LEVEL_DIRECTORY  "config/map_levels.txt"

int FileInterpreter::loadLevel(Level* levels, QFPair* level_info) {
    // Initialisation of variables
    std::string level_name = level_info->getKey();
    std::string level_string;
    int level_rows;
    int level_cols;

    // Look at level_info
    QFDict* level_contents = dynamic_cast<QFDict*>(level_info->getValue());
    if (level_contents == nullptr) {
        return -1;
    }

    // Get level number
    int level_number = dynamic_cast<QFInt*>(level_contents->getValueFromKey("Level Number"))->getValue();
    if (level_number <= 0) {
        return -1;
    }

    QFList* layout = dynamic_cast<QFList*>(level_contents->getValueFromKey("Layout"));
    if (layout == nullptr) {
        return -1;
    } 

    printf("Success3\n");

    //new Level(char level_name[MAX_LEVEL_NAME_LENGTH], char level_string[MAX_LEVEL_CHARACTERS], int level_rows, int level_cols);
    return -1;
}

int FileInterpreter::countLevels(Level* levels, std::set<int> filled_levels) {
    int count = 0;
    while (filled_levels.count(count)) {
        count ++;
    }
    return count;
}

int FileInterpreter::loadLevels(Level* levels) {
    
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

    QFDict* map_levels_dict = dynamic_cast<QFDict*>(level_file_contents.getValueFromKey("Map Levels"));
    if (map_levels_dict == nullptr) {
        printf("%s", "No QFDict in a \"Map Levels\" key found\n");
        return 0;
    }

    printf("Success1!\n");

    std::vector<QFPair*> map_level_pairs = map_levels_dict->getPairs();
    std::set<int> filled_levels;

    for (QFPair* pair : map_level_pairs) {
        filled_levels.insert(loadLevel(levels, pair));
    }

    printf("Success2!\n");

    return countLevels(levels, filled_levels);
} 