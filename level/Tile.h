#ifndef TILE_H
#define TILE_H

#include "../player/Player.h"

enum TileType {
    NULL_TYPE,
    MONSTER
};

class Tile {
    protected:
        TileType tileType;
    
    public:
        // Create a tile from an input character
        static Tile tileFromChar(char c);
        Tile();
        virtual void resolveEffects(Player player);
};

class Monster : public Tile {
    private:
        int health;

    public:
        // Create a monster with specified health
        Monster(int health);

        void resolveEffects(Player player) override;
};

#endif