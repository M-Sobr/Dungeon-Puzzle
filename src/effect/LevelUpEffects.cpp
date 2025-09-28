#include <iostream> 

#include "LevelUpEffects.h"
#include "Effect.h"
#include "../utils/ReadInput.h"

LevelUpEffects::LevelUpEffects() {
    ;
}

void LevelUpEffects::addLevel(std::vector<EffectsList*> effects) {
    levelUpEffects.push_back(effects);
}

EffectsList* LevelUpEffects::chooseLevelUpEffects(int level) {
    std::vector<EffectsList*>* effectChoices = &levelUpEffects.at(level - 2);
    std::vector<std::string> effect_names;
    
    for (EffectsList* e : *effectChoices) {
        effect_names.push_back(e->toString());
    }

    char title[100];
    sprintf_s(title, "You have levelled up to Level %d!\n", level);

    int option = ReadInput::getNumberChoice(title, &effect_names);
    return effectChoices->at(option - 1)->copy();
}
