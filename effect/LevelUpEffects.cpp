#include <iostream> 

#include "LevelUpEffects.h"
#include "Effect.h"

LevelUpEffects::LevelUpEffects() {
    // Temporary
    EffectsList* e = new EffectsList();
    e->addEffect(new Effect(EffectTypes::GAIN_MAX_HEALTH, 2));
    EffectsList* f = new EffectsList();
    f->addEffect(new Effect(EffectTypes::GAIN_HEALTH, 5));

    std::vector<EffectsList*> v;
    v.push_back(e);
    v.push_back(f);

    this->addLevel(2, v);
}

void LevelUpEffects::addLevel(int level, std::vector<EffectsList*> effects) {
    levelUpEffects.insert_or_assign(level, effects);
}

EffectsList* LevelUpEffects::chooseLevelUpEffects(int level) {
    std::vector<EffectsList*>* effectChoices = &levelUpEffects.at(level);
    
    // Print effect choices
    printf("You have levelled up to Level %d!\n", level);
    for (int i=0; i < effectChoices->size(); i++) {
        printf("%d) %s\n", i+1, effectChoices->at(i)->toString().c_str());
    }

    char s[10];
    while (true) {
        // Get user input
        std::cout << "> ";
        std::cin >> s;
        int option = atoi(s);
        if (option > 0 && option <= effectChoices->size()) {
            std::cout << '\n';
            return effectChoices->at(option - 1);
        }
    }
}
