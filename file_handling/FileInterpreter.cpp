#include <exception>
#include <stdexcept>

#include "FileInterpreter.h"
#include "FileReader.h"
#include "../level/Level.h"
#include "qf_types/QFTypes.h"

#define MAP_LEVEL_DIRECTORY  "config/map_levels.txt"


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

    QFDict* map_levels = dynamic_cast<QFDict*>(level_file_contents.getValueFromKey("Map Levels"));
    if (map_levels == nullptr) {
        printf("%s", "No QFDict in a \"Map Levels\" key found\n");
        return 0;
    }

    printf("Success!\n");
    
    // printf("Return Value: %d\n\n", level_file_reader.readFile(&level_file_contents));
    return 0;
} 