#include "Tile.h"

Tile Tile::tileFromChar(char c) {
    if ('0' <= c && c <= '9') {
        return Monster::Monster(c - '0');
    }
    return Tile::Tile();
}

Tile::Tile() {
    this->tileType = TileType::NULL_TYPE;
}

Monster::Monster(int h) {
    this->health = h;
    this->tileType = TileType::MONSTER;
}

void Monster::resolveEffects(Player p) {

}