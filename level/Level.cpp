#include "Level.h"
#include "Tile.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

Level::Level() {
}    

Level::Level(std::string level_name, char level_string[MAX_LEVEL_CHARACTERS], int level_rows, int level_cols) :
    name(level_name), rows(level_rows), cols(level_cols) {
    
    int i;

    objective_tiles = 0;
    level_beaten = false;

    int row = 0;
    int col = 0;
    for (i=0; level_string[i] != '\0'; i++) {
        switch (level_string[i]) {
            case '\n':
                while (col < level_cols) {
                    contents[row][col] = 'X';
                    col ++;
                }
                contents[row][col] = '\0';
                row ++;
                col = 0;
                break;
            case PLAYER_TILE:
                player_pos[0] = row;
                player_pos[1] = col;
                symbolUnderPlayer = EMPTY_TILE;
                contents[row][col] = PLAYER_TILE;
                col ++;
                break;
            default:
                contents[row][col] = level_string[i];
                col ++;
        }
        switch (tileTypeFromChar(level_string[i])) {
            case Tile_Type::MONSTER:
            case Tile_Type::HEAL:
                objective_tiles += 1;
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

void Level::getPlayerPos(int pos_ptr[2]) {
    pos_ptr[0] = this->player_pos[0];
    pos_ptr[1] = this->player_pos[1];
}

Tile* Level::getTileAtPosition(int row, int col) {
    return Tile::tileFromChar(contents[row][col]);
}

bool Level::isBeaten() {
    return level_beaten;
}

void Level::movePlayerTo(int row, int col) {
    // Check if there is any movement
    if (contents[row][col] == PLAYER_TILE) {
        return;
    }

    // Move the player and update symbolUnderPlayer
    contents[player_pos[0]][player_pos[1]] = symbolUnderPlayer;
    symbolUnderPlayer = contents[row][col];
    contents[row][col] = PLAYER_TILE;
    
    player_pos[0] = row;
    player_pos[1] = col;

    // Resolve effects from moving onto a special tile type.
    switch (tileTypeFromChar(symbolUnderPlayer)) {
        case Tile_Type::MONSTER:
        case Tile_Type::HEAL:
            symbolUnderPlayer = EMPTY_TILE;
            objective_tiles -= 1;
            break;
        case Tile_Type::OBJECTIVE:
            if (objective_tiles == 0) {
                level_beaten = true;
            }    
    }
}

void Level::resetPlayerTo(int row, int col, Tile* tile_at_player) {
    // Check if there is any movement
    if (contents[row][col] == PLAYER_TILE) {
        return;
    }

    // Move the player and update tiles
    contents[player_pos[0]][player_pos[1]] = tile_at_player->getChar();
    symbolUnderPlayer = contents[row][col];
    contents[row][col] = PLAYER_TILE;
    
    player_pos[0] = row;
    player_pos[1] = col;

    if (tile_at_player->isObjective()) {
        objective_tiles += 1;
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

int Level::calculateMovementDestination(int* dest_row, int* dest_col, 
int row_direction, int col_direction, int movement) {

    *dest_row = player_pos[0];
    *dest_col = player_pos[1];
    
    // Find any '#' tiles for the player to move to
    for (int i=0; i<movement; i++) {
        *dest_row += row_direction;
        *dest_col += col_direction;
        if (this->tileOutsideLevel(*dest_row, *dest_col)) {
            return 0;
        }
        if (contents[*dest_row][*dest_col] == '#') {
            return i + 1;
        }
    }

    return this->tileIsWall(*dest_row, *dest_col) ? 0 : movement;
}