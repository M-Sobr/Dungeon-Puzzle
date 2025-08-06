#include "level/Level.h"

#include <iostream>
#include <string>

#define LEVEL_COUNT 10

int main(void) {
    Level levels[LEVEL_COUNT];
    loadLevels(levels);
    levels[0].printLevel();
}