#ifndef EFFECT_H
#define EFFECT_H

#include <vector>
#include <string>
#include <exception>

#define MAX_EFFECT_LINE_LENGTH 20

enum EffectTypes {
    GAIN_MAX_HEALTH,
    GAIN_HEALTH,
    GAIN_EXPERIENCE,
    GAIN_MOVEMENT,
    TAKE_DAMAGE
};

class Player;

class InvalidEffectNameException : public std::exception {
    private:
        std::string msg;

    public:
        InvalidEffectNameException(const std::string msg);
        const char* what();
};

class Effect {
    private:
        EffectTypes type;
        int value;

    public:
        Effect(EffectTypes type, int value);
        Effect(const char type_string[], int value);
        void applyEffect(Player* player);
        void undoEffect(Player* player);
        /** Copy this effect and return a new effect */
        Effect* copy();
        std::string toString();
};

class EffectsList {
    private:
        std::vector<Effect*> effects;
    
    public:
        EffectsList();
        ~EffectsList();
        int size();
        void addEffect(Effect* effect);
        Effect* popEffect();
        EffectsList* copy();
        std::string toString();
};


#endif //EFFECT_H