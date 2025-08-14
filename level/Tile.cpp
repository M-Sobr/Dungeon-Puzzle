#include "Tile.h"

Tile Tile::tileFromChar(char c) {
    if ('0' <= c && c <= '9') {
        return Monster::Monster(c - '0');
    }
    return NullTile::NullTile();
}

Monster::Monster(int h) {
    this->health = h;
}

void Monster::resolveEffects(Player p) {
    p.takeDamage(this->health);
    p.gainExperience(this->health);
}