#include "Effect.h" 
#include "../player/Player.h"
#include "../utils/Utils.h"

InvalidEffectNameException::InvalidEffectNameException(const std::string m) {
    this->msg = m;
}

const char* InvalidEffectNameException::what() {
    return msg.c_str();
}

Effect::Effect(EffectTypes t, int v) : 
    type(t), value(v) {
}

Effect::Effect(const char type_string[], int v) :
    value(v) {

    if (equalsIgnoreCase(type_string, "GAIN_MAX_HEALTH", 16)) {
        this->type = EffectTypes::GAIN_MAX_HEALTH;
    } else if (equalsIgnoreCase(type_string, "GAIN_HEALTH", 12)) {
        this->type = EffectTypes::GAIN_HEALTH;
    } else if (equalsIgnoreCase(type_string, "GAIN_EXPERIENCE", 12)) {
        this->type = EffectTypes::GAIN_EXPERIENCE;
    } else if (equalsIgnoreCase(type_string, "TAKE_DAMAGE", 12)) {
        this->type = EffectTypes::TAKE_DAMAGE;
    } else if (equalsIgnoreCase(type_string, "GAIN_MOVEMENT", 14)) {
        this->type = EffectTypes::GAIN_MOVEMENT;
    } else {
        std::string s;
        throw new InvalidEffectNameException(s.append(type_string).append(" is not a valid effect type name!"));
    }
}

void Effect::applyEffect(Player* player) {
    switch (this->type) {
        case EffectTypes::GAIN_MAX_HEALTH:
            player->increaseMaxHealth(this->value);
            break;
        case EffectTypes::GAIN_HEALTH:
            this->value = player->heal(this->value);
            break;   
        case EffectTypes::GAIN_EXPERIENCE:
            player->gainExperience(this->value);
            break;
        case EffectTypes::TAKE_DAMAGE:
            player->takeDamage(this->value);
            break;  
        case EffectTypes::GAIN_MOVEMENT:
            player->gainMovement(this->value);
            break;    
    }
}

void Effect::undoEffect(Player* player) {
    switch (this->type) {
        case EffectTypes::GAIN_MAX_HEALTH:
            player->increaseMaxHealth(-this->value);
            break;
        case EffectTypes::GAIN_HEALTH:
            player->heal(-this->value);
            break;
        case EffectTypes::GAIN_EXPERIENCE:
            player->gainExperience(-this->value);
            break;
        case EffectTypes::TAKE_DAMAGE:
            player->heal(this->value);
            break; 
        case EffectTypes::GAIN_MOVEMENT:
            player->gainMovement(-this->value);
            break;                   
    }
}

Effect* Effect::copy() {
    return new Effect(this->type, this->value);
}

std::string Effect::toString() {
    std::string s;
    char c[MAX_EFFECT_LINE_LENGTH];
    
    switch (this->type) {
        case EffectTypes::GAIN_MAX_HEALTH:
            sprintf_s(c, "+%d Max Health", this->value);
            break;
        case EffectTypes::GAIN_HEALTH:
            sprintf_s(c, "+%d Health", this->value);  
            break;
        case EffectTypes::GAIN_EXPERIENCE:
            sprintf_s(c, "+%d XP", this->value);
            break;
        case EffectTypes::TAKE_DAMAGE:
            sprintf_s(c, "-%d Health", this->value);
            break;
    }
    s.append(c);
    return s;
}

EffectsList::EffectsList() {
}

EffectsList::~EffectsList() {
    while (effects.size() > 0) {
        delete this->popEffect();
    }
}

int EffectsList::size() {
    return (int)effects.size();
}

void EffectsList::addEffect(Effect* e) {
    this->effects.push_back(e);
}

Effect* EffectsList::popEffect() {
    Effect* e = this->effects.back();
    this->effects.pop_back();
    return e;
}

EffectsList* EffectsList::copy() {
    EffectsList* e = new EffectsList();
    for (Effect* effect : this->effects) {
        e->addEffect(effect->copy());
    }
    return e;
}

std::string EffectsList::toString() {
    std::string s;
    int last_effect_index = (int)this->effects.size() - 1;
    for (int i=0; i < last_effect_index; i++) {
        s.append(this->effects.at(i)->toString()).append(",\n   ");
    }
    return s.append(this->effects.at(last_effect_index)->toString());
}


