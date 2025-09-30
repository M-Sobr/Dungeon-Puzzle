#ifndef LEVEL_UP_EFFECTS_H
#define LEVEL_UP_EFFECTS_H

#include <vector>
#include <map>

class EffectsList;
class EffectChoices;

class LevelUpEffects {
    private:
        std::vector<EffectChoices*> levelUpEffects;

    public:
        LevelUpEffects();
        void addLevel(EffectChoices* effects);
        EffectsList* chooseLevelUpEffects(int level);
};

#endif  // LEVEL_UP_EFFECTS_H