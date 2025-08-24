#include "Effect.h" 
#include "../player/Player.h"

Effect::Effect(EffectTypes t, int v) {
    this->type = t;
    this->value = v;
}

void Effect::applyEffect(Player* player) {
    switch (this->type) {
        case EffectTypes::GAIN_MAX_HEALTH:
            player->increaseMaxHealth(this->value);
            break;
        case EffectTypes::GAIN_HEALTH:
            player->heal(this->value);
            break;    
    }
}

std::string Effect::toString() {
    char s[MAX_EFFECT_LINE_LENGTH];
    switch (this->type) {
        case EffectTypes::GAIN_MAX_HEALTH:
            sprintf_s(s, "+%d Max Health", this->value);
            break;
        case EffectTypes::GAIN_HEALTH:
            sprintf_s(s, "+%d Health", this->value);      

    }
    return s;
}

EffectsList::EffectsList() {
}

void EffectsList::addEffect(Effect* e) {
    this->effects.push_back(e);
}

Effect* EffectsList::popEffect() {
    Effect* e = this->effects.back();
    this->effects.pop_back();
    return e;
}

Effect* EffectsList::chooseEffect(char title[]) {
    // Print out dialogue for effect choosing
    std::cout << title << '\n';
    for (int i=0; i < this->effects.size(); i++) {
        std::cout << i+1 << ") " << this->effects.at(i)->toString() << '\n';
    }
    char s[10];
    while (true) {
        // Get user input
        std::cin >> s;
        int option = atoi(s);
        if (option > 0) {
            return this->effects.at(option - 1);
        }
    }
}

