#include "Tile.h"
#include "../player/Player.h"
#include "../effect/Effect.h"

#include <set>

std::set<char> special_chars = {
    'C'
};

Tile_Type tileTypeFromChar(char c) {
    if ('0' <= c && c <= '9') {
        return Tile_Type::MONSTER;
    } else if (c == '+') {
        return Tile_Type::HEAL;
    } else if (c == '*') {
        return Tile_Type::FINISH;
    } else if (isSpecialTile(c)) {
        return Tile_Type::SPECIAL;
    }
    return Tile_Type::NULL_TILE;
}

bool inline isSpecialTile(char c) {
    return special_chars.count(c);
}

Tile::Tile(char ch) : c(ch) {
    ;
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

NullTile::NullTile(char ch) : Tile::Tile(ch) {
    ;
};

void NullTile::resolveEffects(Player*) {};

bool NullTile::isObjective() {
    return false;
}

bool NullTile::isSpecial() {
    return false;
}

Monster::Monster(char ch) : 
    Tile::Tile(ch), health(ch - '0') {
    
    ;
}

void Monster::resolveEffects(Player* p) {
    p->applyEffect(new Effect(EffectTypes::TAKE_DAMAGE, this->health));
    p->applyEffect(new Effect(EffectTypes::GAIN_EXPERIENCE, this->health));
}

bool Monster::isObjective() {
    return true;
}

bool Monster::isSpecial() {
    return false;
}

HealTile::HealTile() : Tile::Tile(HEAL_TILE) {
    ;
};

void HealTile::resolveEffects(Player* p) {
    p->applyEffect(new Effect(EffectTypes::GAIN_HEALTH, PLAYER_MAXIMUM_HEALTH));
}

bool HealTile::isObjective() {
    return true;
}

bool HealTile::isSpecial() {
    return false;
}