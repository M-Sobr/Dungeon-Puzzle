#include "Tile.h"

Tile_Type tileTypeFromChar(char c) {
    if ('0' <= c && c <= '9') {
        return Tile_Type::MONSTER_TILE;
    } else if (c == '+') {
        return Tile_Type::HEAL_TILE;
    } else if (c == '*') {
        return Tile_Type::OBJECTIVE_TILE;
    }
    return Tile_Type::NULL_TILE;
}

Tile* Tile::tileFromChar(char c) {
    switch (tileTypeFromChar(c)) {
        case Tile_Type::MONSTER_TILE:
            return new Monster(c - '0'); 
        case Tile_Type::HEAL_TILE:
            return new HealTile();
        default:
            return new NullTile();
    }
}

Monster::Monster(int h) {
    this->health = h;
}

void Monster::resolveEffects(Player* p) {
    p->applyEffect(new Effect(EffectTypes::TAKE_DAMAGE, this->health));
    p->applyEffect(new Effect(EffectTypes::GAIN_EXPERIENCE, this->health));
}

void HealTile::resolveEffects(Player* p) {
    p->applyEffect(new Effect(EffectTypes::GAIN_HEALTH, PLAYER_MAXIMUM_HEALTH));
}