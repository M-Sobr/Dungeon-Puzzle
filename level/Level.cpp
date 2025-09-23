#include "Level.h"
#include "Tile.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

Level::Level() {
}    

Level::Level(std::string level_name, std::vector<LevelLayer> layers, int* p_pos, int start_layer, int obj_tiles) : 
    
    name(level_name), layout_layers(layers), currentLayerIndex(start_layer), currentLayer(layers.at(start_layer)),
    symbolUnderPlayer(EMPTY_TILE), objective_tiles(obj_tiles), level_beaten(false) {
    
    player_pos[0] = p_pos[0];
    player_pos[1] = p_pos[1];
}

void Level::printName() {
    std::cout << name << '\n';
}
    
void Level::printLevel() {
    for (int i=0; i < currentLayer.rows; i++) {
        std::cout << currentLayer.contents[i] << '\n';
    }
    std::cout << '\n';
}

int inline Level::getRowCount() {
    return currentLayer.rows;
}
int inline Level::getColCount() {
    return currentLayer.cols;
}

void Level::getPlayerPos(int pos_ptr[2]) {
    pos_ptr[0] = this->player_pos[0];
    pos_ptr[1] = this->player_pos[1];
}

Tile* Level::getTileAtPosition(int row, int col) {
    return Tile::tileFromChar(currentLayer.contents[row][col]);
}

bool Level::isBeaten() {
    return level_beaten;
}

void Level::movePlayerTo(int row, int col) {
    // Check if there is any movement
    if (currentLayer.contents[row][col] == PLAYER_TILE) {
        return;
    }

    // Move the player and update symbolUnderPlayer
    currentLayer.contents[player_pos[0]][player_pos[1]] = symbolUnderPlayer;
    symbolUnderPlayer = currentLayer.contents[row][col];
    currentLayer.contents[row][col] = PLAYER_TILE;
    
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
    if (currentLayer.contents[row][col] == PLAYER_TILE) {
        return;
    }

    // Move the player and update tiles
    currentLayer.contents[player_pos[0]][player_pos[1]] = tile_at_player->getChar();
    symbolUnderPlayer = currentLayer.contents[row][col];
    currentLayer.contents[row][col] = PLAYER_TILE;
    
    player_pos[0] = row;
    player_pos[1] = col;

    if (tile_at_player->isObjective()) {
        objective_tiles += 1;
    }
}

bool inline Level::tileOutsideLevel(int row, int col) {
    return (row < 0 || row >= this->currentLayer.rows || col < 0 || col >= this->currentLayer.cols);
}

bool inline Level::tileIsWall(int row, int col) {
    return (tileOutsideLevel(row, col) || currentLayer.contents[row][col] == 'X');
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
        if (currentLayer.contents[*dest_row][*dest_col] == '#') {
            return i + 1;
        }
    }

    return this->tileIsWall(*dest_row, *dest_col) ? 0 : movement;
}