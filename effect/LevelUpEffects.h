#ifndef LEVEL_UP_EFFECTS_H
#define LEVEL_UP_EFFECTS_H

#include <vector>
#include <map>

class EffectsList;

class LevelUpEffects {
    private:
        std::map<int, std::vector<EffectsList*>> levelUpEffects;

    public:
        LevelUpEffects();
        void addLevel(int level, std::vector<EffectsList*> effects);
        EffectsList* chooseLevelUpEffects(int level);
};

#endif  // LEVEL_UP_EFFECTS_H