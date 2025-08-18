#include "Level.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#define PLAYER_TILE 'P'
#define EMPTY_TILE '_'

const char LEVEL_1[MAX_LEVEL_CHARACTERS] = "PXX____\n_X1__X_\n___X+X_\nX+__X_1\n1___X__\n_X_X*__\n";

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
        } else if (level_string[i] == PLAYER_TILE) {
            player_pos[0] = row;
            player_pos[1] = col;
            symbolUnderPlayer = EMPTY_TILE;
            contents[row][col] = PLAYER_TILE;
            col ++;
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

int inline Level::getRowCount() {
    return rows;
}
int inline Level::getColCount() {
    return cols;
}

Tile Level::getTileAtPosition(int row, int col) {
    return Tile::tileFromChar(contents[row][col]);
}

void Level::movePlayerTo(int row, int col) {
    contents[player_pos[0]][player_pos[1]] = symbolUnderPlayer;
    symbolUnderPlayer = contents[row][col];
    contents[row][col] = PLAYER_TILE;
    
    player_pos[0] = row;
    player_pos[1] = col;

    // Check symbol and change to empty if it was a monster
    if (('0' <= symbolUnderPlayer) && (symbolUnderPlayer <= '9')) {
        symbolUnderPlayer = EMPTY_TILE;
    }
}

bool inline Level::tileOutsideLevel(int row, int col) {
    return (row < 0 || row >= this->rows || col < 0 || col >= this->cols);
}

bool inline Level::tileIsWall(int row, int col) {
    return (tileOutsideLevel(row, col) || contents[row][col] == 'X');
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

bool Level::calculateMovementDestination(int* dest_row, int* dest_col, 
int row_direction, int col_direction, int movement) {

    *dest_row = player_pos[0];
    *dest_col = player_pos[1];
    
    // Find any '#' tiles for the player to move to
    for (int i=0; i<movement; i++) {
        *dest_row += row_direction;
        *dest_col += col_direction;
        if (this->tileOutsideLevel(*dest_row, *dest_col)) {
            return false;
        }
        if (contents[*dest_row][*dest_col] == '#') {
            return true;
        }
    }

    return !this->tileIsWall(*dest_row, *dest_col);
}