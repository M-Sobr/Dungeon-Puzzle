#ifndef EFFECT_H
#define EFFECT_H

#include <vector>
#include <string>

#define MAX_EFFECT_LINE_LENGTH 20

enum EffectTypes {
    GAIN_MAX_HEALTH,
    GAIN_HEALTH,
    GAIN_EXPERIENCE,
    TAKE_DAMAGE
};

class Player;

class Effect {
    private:
        EffectTypes type;
        int value;

    public:
        Effect(EffectTypes type, int value);
        int applyEffect(Player* player);
        void undoEffect(Player* player);
        std::string toString();
};

class EffectsList {
    private:
        std::vector<Effect*> effects;
    
    public:
        EffectsList();
        void addEffect(Effect* effect);
        Effect* popEffect();
        Effect* chooseEffect(char title[]);
};


#endif //EFFECT_H