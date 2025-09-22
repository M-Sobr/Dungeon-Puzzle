#include "Level.h"

Level::LevelBuilder::LevelBuilder() : necessary_fields_set(0) {
    ;
}

Level::LevelBuilder* Level::LevelBuilder::setName(std::string name) {
    this->level_name = name;
    return this;
}

Level::LevelBuilder* Level::LevelBuilder::addLayer(LevelLayer layer) {
    return this;
}

Level* Level::LevelBuilder::build() {
    if (necessary_fields_set < 5) {
        return nullptr;
    }
    return new Level(this->level_name, this->layout_layers, this->player_pos, this->start_layer, this->objective_tiles);
}