#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>

#define MAX_LEVEL_NAME_LENGTH 20
#define MAX_LEVEL_CHARACTERS 1000

#define MAX_LEVEL_WIDTH 10
#define MAX_LEVEL_HEIGHT 10

class Level {
    private:
        char name[MAX_LEVEL_NAME_LENGTH];
        char contents[MAX_LEVEL_CHARACTERS];

    public:
        Level();
        Level(char level_name[], char level_string[]);
        void printLevel();
        void printName();
};

void loadLevels(Level* levels);

#endif