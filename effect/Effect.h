#ifndef EFFECT_H
#define EFFECT_H

#include "../player/Player.h"
#include <vector>
#include <string>

#define MAX_EFFECT_LINE_LENGTH 20

enum EffectTypes {
    GAIN_MAX_HEALTH,
    GAIN_HEALTH
};

class Effect {
    private:
        EffectTypes type;
        int value;

    public:
        Effect(EffectTypes type, int value);
        void applyEffect(Player* player);
        std::string toString();
};

class EffectsList {
    private:
        std::vector<Effect> effects;
    
    public:
        EffectsList();
        void addEffect(Effect* effect);
        Effect chooseEffect(char title[]);
};


#endif //EFFECT_H