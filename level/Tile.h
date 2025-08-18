#ifndef TILE_H
#define TILE_H

#include "../player/Player.h"

class Tile {    
    public:
        // Create a tile from an input character
        static Tile tileFromChar(char c);
        virtual void resolveEffects(Player* /*player*/) {};
};

// Exists for a tile with no special effects
class NullTile : public Tile {
    public:
        NullTile() {};
        void resolveEffects(Player* /*player*/) override {};
};

class Monster : public Tile {
    private:
        int health;

    public:
        // Create a monster with specified health
        Monster(int health);

        void resolveEffects(Player* player) override;
};

#endif