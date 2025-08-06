#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>


class Level {
    private:
        std::string level;

    public:
        Level();
        Level(char level_string[1000]);
        void printLevel();
};

void loadLevels(Level* levels);

#endif