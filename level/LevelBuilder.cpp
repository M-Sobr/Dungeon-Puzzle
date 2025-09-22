#include "Level.h"

Level::LevelBuilder::LevelBuilder() : necessary_fields_set(0) {
    ;
}

Level* Level::LevelBuilder::build() {
    if (necessary_fields_set < 5) {
        return new Level();
    }
    return new Level(this->level_name, this->layout_layers, this->player_pos, this->start_layer, this->objective_tiles);
}