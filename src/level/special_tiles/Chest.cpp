#include "../Tile.h"
#include "../../effect/Effect.h"

ChestTile::ChestTile() : Tile::Tile(CHEST) {
    ;
};

void ChestTile::resolveEffects(Player* p) {
    ;
}

bool ChestTile::isObjective() {
    return true;
}

bool ChestTile::isSpecial() {
    return true;
}

ChestTile::ChestBuilder::ChestBuilder() {
    ;
}

ChestTile::ChestBuilder* ChestTile::ChestBuilder::setPosition(int chest_pos[3]) {
    this->pos[0] = chest_pos[0];
    this->pos[1] = chest_pos[1];
    this->pos[2] = chest_pos[2];
    printf("[%d, %d, %d]\n", pos[0], pos[1], pos[2]);
    return this;
}