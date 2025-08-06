#include "Level.h"

#include <iostream>
#include <string>
#include <fstream>


char LEVEL_1[1000] = "PXX____\n_X1__X_\n___X+X_\nX+__X_1\n1___X__\n_X_X*__\n";

Level::Level() {
    level = "";
}    

Level::Level(char level_string[1000]) {
    level = level_string;
}
    
void Level::printLevel() {
    std::cout << level;
}

void loadLevels(Level* levels) {
    char txt[100];
    std::ifstream levels_data("level/levels.txt");
    
    while (levels_data.getline(txt, 20)) {
        std::cout << txt << "\n";
    }

    levels_data.close();

    levels[0] = Level::Level(LEVEL_1);
}