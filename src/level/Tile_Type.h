
#ifndef TILE_TYPE_H
#define TILE_TYPE_H

#define PLAYER_TILE 'P'
#define EMPTY_TILE '_'
#define HEAL_TILE '+'

enum Tile_Type {
    NULL_TILE,
    MONSTER,
    HEAL,
    CHEST,
    FINISH,
    SPECIAL
};

#endif // TILE_TYPE_H