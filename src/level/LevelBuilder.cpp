#include "Level.h"
#include "Tile.h"
#include "../file_handling/FileExceptions.h"

Level::LevelBuilder::LevelBuilder() : necessary_fields_set(0), start_layer(-1), objective_tiles(0) {
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
        return false;
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
                this->addPlayer(i, j, ((int)layout_layers.size()) - 1);
                continue;
            }
            switch (tileTypeFromChar(tile_char)) {
                case Tile_Type::MONSTER:
                case Tile_Type::HEAL:
                    objective_tiles += 1;
            }
        }
    }
    return this;
}

Level* Level::LevelBuilder::build() {
    if (necessary_fields_set < 2) {
        throw new LevelBuilderException("Not enough level fields set!");
    }
    return new Level(this->level_name, this->layout_layers, this->player_pos, this->start_layer, this->objective_tiles);
}