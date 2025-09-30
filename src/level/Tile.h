#ifndef TILE_H
#define TILE_H

class Player;

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

Tile_Type tileTypeFromChar(char c);
bool isSpecialTile(char c);

class Tile {    
    private:
        char c;
    
    public:
        Tile(char c);
        virtual ~Tile() {};
        char getChar();

        virtual bool isObjective() = 0;
        virtual bool isSpecial() = 0;

        // Create a tile from an input character
        static Tile* tileFromChar(char c);
        
        // Returns the number of effects applied
        virtual void resolveEffects(Player* /*player*/) = 0;
};

// Exists for a tile with no special effects
class NullTile : public Tile {
    public:
        NullTile(char c);
        ~NullTile() {};
        bool isObjective() override;
        bool isSpecial() override;

        void resolveEffects(Player* /*player*/) override;
};

class Monster : public Tile {
    private:
        int health;

    public:
        // Create a monster with specified health
        Monster(char c);
        ~Monster() {};
        bool isObjective() override;
        bool isSpecial() override;

        void resolveEffects(Player* player) override;
};

class HealTile : public Tile {
    private:

    public:
        HealTile();
        ~HealTile() {};
        bool isObjective() override;
        bool isSpecial() override;

        void resolveEffects(Player* player) override;
};

class ChestTile : public Tile {
    private:

    public:
        ChestTile();
        ~ChestTile() {};
        bool isObjective() override;
        bool isSpecial() override;

        void resolveEffects(Player* player) override;

        class ChestBuilder {
            
        };
};

#endif // TILE_H