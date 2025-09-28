#include <iostream> 

#include "LevelUpEffects.h"
#include "Effect.h"

LevelUpEffects::LevelUpEffects() {
    ;
}

void LevelUpEffects::addLevel(std::vector<EffectsList*> effects) {
    levelUpEffects.push_back(effects);
}

EffectsList* LevelUpEffects::chooseLevelUpEffects(int level) {
    std::vector<EffectsList*>* effectChoices = &levelUpEffects.at(level - 2);
    
    // Print effect choices
    printf("You have levelled up to Level %d!\n", level);
    for (int i=0; i < effectChoices->size(); i++) {
        printf("%d) %s\n", i+1, effectChoices->at(i)->toString().c_str());
    }

    std::string s;
    while (true) {
        // Get user input
        printf("> ");
        std::cin >> s;
        int option = atoi(s.c_str());
        if (option > 0 && option <= effectChoices->size()) {
            printf("\n");
            return effectChoices->at(option - 1)->copy();
        }
    }
}
