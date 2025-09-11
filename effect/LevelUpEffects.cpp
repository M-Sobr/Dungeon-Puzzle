#include "LevelUpEffects.h"
#include "Effect.h"

EffectsList* getEffectsListFromLevel(int level) {
    switch (level) {
        case 2:
            EffectsList* e = new EffectsList();
            e->addEffect(new Effect(EffectTypes::GAIN_MAX_HEALTH, 2));
            e->addEffect(new Effect(EffectTypes::GAIN_HEALTH, 5));
            return e;
    }
    return new EffectsList();
}
