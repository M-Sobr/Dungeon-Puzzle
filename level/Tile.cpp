#include "Tile.h"
#include "../player/Player.h"
#include "../effect/Effect.h"

Tile_Type tileTypeFromChar(char c) {
    if ('0' <= c && c <= '9') {
        return Tile_Type::MONSTER;
    } else if (c == '+') {
        return Tile_Type::HEAL;
    } else if (c == '*') {
        return Tile_Type::OBJECTIVE;
    }
    return Tile_Type::NULL_TILE;
}

Tile::Tile(char ch) {
    this->c = ch;
}

char Tile::getChar() {
    return this->c;
}

Tile* Tile::tileFromChar(char c) {
    switch (tileTypeFromChar(c)) {
        case Tile_Type::MONSTER:
            return new Monster(c); 
        case Tile_Type::HEAL:
            return new HealTile();
        default:
            return new NullTile(c);
    }
}

NullTile::NullTile(char ch) : Tile::Tile(ch) {};

void NullTile::resolveEffects(Player*) {};

bool NullTile::isObjective() {
    return false;
}

Monster::Monster(char ch) : Tile::Tile(ch) {
    this->health = ch - '0';
}

void Monster::resolveEffects(Player* p) {
    p->applyEffect(new Effect(EffectTypes::TAKE_DAMAGE, this->health));
    p->applyEffect(new Effect(EffectTypes::GAIN_EXPERIENCE, this->health));
}

bool Monster::isObjective() {
    return true;
}

HealTile::HealTile() : Tile::Tile(HEAL_TILE) {};

void HealTile::resolveEffects(Player* p) {
    p->applyEffect(new Effect(EffectTypes::GAIN_HEALTH, PLAYER_MAXIMUM_HEALTH));
}

bool HealTile::isObjective() {
    return true;
}