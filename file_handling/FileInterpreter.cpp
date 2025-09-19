#include "FileInterpreter.h"
#include "FileReader.h"
#include "../level/Level.h"
#include "qf_types/QFTypes.h"

#define MAP_LEVEL_DIRECTORY  "config/map_levels.txt"

int FileInterpreter::loadLevels(Level* levels) {
    FileReader level_file_reader(MAP_LEVEL_DIRECTORY);
    QFDict level_file_contents;
    printf("Return Value: %d\n\n", level_file_reader.readFile(&level_file_contents));
    return 0;
} 