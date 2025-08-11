#include "Level.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


char LEVEL_1[MAX_LEVEL_CHARACTERS] = "PXX____\n_X1__X_\n___X+X_\nX+__X_1\n1___X__\n_X_X*__\n";

Level::Level() {
}    

Level::Level(char level_name[MAX_LEVEL_NAME_LENGTH], char level_string[MAX_LEVEL_CHARACTERS], int level_rows, int level_cols) {
    int i;
    for (i=0; level_name[i] != '\0'; i++) {
        name[i] = level_name[i];
    }
    name[i] = '\0';
    rows = level_rows;
    cols = level_cols;
    int row = 0;
    int col = 0;
    for (i=0; level_string[i] != '\0'; i++) {
        if (level_string[i] == '\n') {
            while (col < level_cols) {
                contents[row][col] = 'X';
                col ++;
            }
            contents[row][col] = '\0';
            row ++;
            col = 0;
        } else {
            contents[row][col] = level_string[i];
            col ++;
        }
    }
}

void Level::printName() {
    std::cout << name << '\n';
}
    
void Level::printLevel() {
    for (int i=0; i<rows; i++) {
        std::cout << contents[i] << '\n';
    }
    std::cout << '\n';
}

int Level::getRowCount() {
    return rows;
}
int Level::getColCount() {
    return cols;
}
char Level::getPosition(int row, int col) {
    return contents[row][col];
}

int loadLevels(Level* levels) {
    char txt[1000];
    std::ifstream levels_data("level/levels.txt");
    
    int level_count;
    // Get amount of levels
    levels_data.getline(txt, 20);
    level_count = atoi(txt);

    int level_index = 0;
    while (level_index < level_count) {
        
        // Get level name
        char level_name[MAX_LEVEL_NAME_LENGTH];
        int level_name_index = 0;
        levels_data.get();
        
        while (levels_data.peek() != '"') {
            level_name[level_name_index] = (char)levels_data.get();
            level_name_index ++;
        }
        level_name[level_name_index] = '\0';
        levels_data.get(txt, 2);

        // Get amount of lines this level takes up
        levels_data.getline(txt, 20);
        int level_line_count = atoi(txt);

        // Get level contents:
        int level_content_index = 0;
        int line_number = 0;
        int max_col_count = 0;
        int current_col_count = 0;
        while (line_number < level_line_count) {
            txt[level_content_index] = (char)levels_data.get();
            if (txt[level_content_index] == '\n' || txt[level_content_index] == EOF) {
                line_number ++;
                if (current_col_count > max_col_count) {
                    max_col_count = current_col_count;
                }
                current_col_count = -1;
            }
            current_col_count ++;
            level_content_index ++;
        }
        txt[level_content_index - 1] = '\n';
        txt[level_content_index] = '\0';
        levels[level_index] = Level::Level(level_name, txt, level_line_count, max_col_count);
        level_index ++;
    }


    levels_data.close();
    return level_count;
}