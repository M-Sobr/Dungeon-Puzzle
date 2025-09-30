#include <iostream> 

#include "LevelUpEffects.h"
#include "Effect.h"
#include "../utils/ReadInput.h"

LevelUpEffects::LevelUpEffects() {
    ;
}

void LevelUpEffects::addLevel(EffectChoices* effects) {
    levelUpEffects.push_back(effects);
}

EffectsList* LevelUpEffects::chooseLevelUpEffects(int level) {
    EffectChoices* effectChoices = levelUpEffects.at(level - 2);
    std::vector<std::string> effect_names;
    
    char title[100];
    sprintf_s(title, "You have levelled up to Level %d!\n", level);

    return effectChoices->chooseEffectList(title);
}
