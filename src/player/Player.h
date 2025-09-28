#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

#include "../effect/Effect.h"

#define PLAYER_MAXIMUM_HEALTH 255

class Player {
    private:
        std::string name;
        int level;
        int health;
        int max_health;
        int movement;
        int currentXp;
        int xpRequired;
        bool is_alive;
        EffectsList appliedEffects;

        void levelUp();
        void levelDown();
    
    public:

        /** A counter for how many effects have been applied to this player this turn. */
        int effect_counter;

        Player(std::string input_name);
        void printDetails();
        int getMovement();
        void takeDamage(int damage);
        void gainExperience(int experience);
        int heal();
        int heal(int health);
        void increaseMaxHealth(int health);
        bool isAlive();
        void applyEffect(Effect* e);
        void applyEffects(EffectsList* e);
        void undoEffect();
};

#endif