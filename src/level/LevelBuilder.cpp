#include "Level.h"
#include "Tile.h"
#include "../file_handling/FileExceptions.h"

Level::LevelBuilder::LevelBuilder() : necessary_fields_set(0), start_layer(-1), objective_tiles(0), finish_tiles(0),
    special_tiles(new std::map<int, SpecialTile*>()) {
    ;
}

bool Level::LevelBuilder::addPlayer(int row, int col, int layer) {
    if (start_layer == -1) {
        this->start_layer = layer;
        this->necessary_fields_set ++;
        this->player_pos[0] = row;
        this->player_pos[1] = col;
        return true;
    
    } else {
        // Player has already been added
        throw new LevelBuilderException("A level cannot have more than one player!");
    }
}

Tile_Type Level::LevelBuilder::getTileTypeAtPosition(int layer, int row, int col) {
    int pos = (layer+1) + 100 * (row+1) + 10000 * (col+1);
    try  {
        return special_tiles->at(pos)->getType();
    } catch (std::out_of_range) {
        char tile_char = this->layout_layers.at(layer).contents[row][col];
        if (isSpecialTile(tile_char)) {
            return Tile_Type::NULL_TILE;
        }
        return tileTypeFromChar(tile_char);
    }
}

void Level::LevelBuilder::checkSpecialTiles() {
    for (int i = 0; i < this->layout_layers.size(); i++) {
        LevelLayer* current_layer = &this->layout_layers.at(i);
        for (int j = 0; j < current_layer->rows; j++) {
            for (int k = 0; k < current_layer->cols; k++) {
                if (tileTypeFromChar(current_layer->contents[j][k]) != getTileTypeAtPosition(i,j,k)) {
                    printf("%d != %d\n", tileTypeFromChar(current_layer->contents[j][k]), getTileTypeAtPosition(i,j,k));
                    char c[60];
                    sprintf_s(c, "Tile mismatch at position [i%d, i%d, i%d]!", i+1, j+1, k+1);
                    throw new LevelBuilderException(c);
                }   
            }
        }
    }
}

Level::LevelBuilder* Level::LevelBuilder::setName(std::string name) {
    this->level_name = name;
    this->necessary_fields_set ++;
    return this;
}

Level::LevelBuilder* Level::LevelBuilder::addLayer(LevelLayer layer) {
    layout_layers.push_back(layer);

    // Check layer for details
    char tile_char;
    for (int i = 0; i < layer.rows; i++) {
        for (int j=0; j < layer.cols; j++) {
            tile_char = layer.contents[i][j];
            if (tile_char == 'P') {
                // Add player tile
                try {
                    this->addPlayer(i, j, ((int)layout_layers.size()) - 1);
                } catch (LevelBuilderException* e) {
                    throw e;
                }
                continue;
            }
            switch (tileTypeFromChar(tile_char)) {
                case Tile_Type::MONSTER:
                case Tile_Type::HEAL:
                    objective_tiles += 1;
                    break;
                case Tile_Type::FINISH:
                    finish_tiles += 1;    
            }
        }
    }
    return this;
}

Level::LevelBuilder* Level::LevelBuilder::addSpecialTile(int pos[3], SpecialTile* tile) {
    special_tiles->insert_or_assign(pos[0] + 100 * pos[1] + 10000 * pos[2], tile);
    return this;
}

Level* Level::LevelBuilder::build() {
    if (necessary_fields_set < 2) {
        throw new LevelBuilderException("Not enough level fields set!");
    } else if (finish_tiles == 0) {
        throw new LevelBuilderException("This level has no finish tile!");
    }
    try {
        this->checkSpecialTiles();
    } catch (LevelBuilderException* e) {
        throw e;
    }
    return new Level(this->level_name, this->layout_layers, this->special_tiles, this->player_pos, this->start_layer, this->objective_tiles);
}