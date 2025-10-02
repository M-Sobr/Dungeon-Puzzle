#include "../Tile.h"
#include "../../effect/Effect.h"
#include "../../player/Player.h"
#include "../../file_handling/FileExceptions.h"

ChestTile::ChestTile(EffectChoices* chest_choices) : 
    SpecialTile::SpecialTile('C'), choices(chest_choices) {
};

void ChestTile::resolveEffects(Player* p) {
    p->applyEffects(choices->chooseEffectList(""));
}

bool ChestTile::isObjective() {
    return true;
}

ChestTile::ChestBuilder::ChestBuilder() : choices_set(0) {
    ;
}

ChestTile::ChestBuilder* ChestTile::ChestBuilder::setChoices(EffectChoices* chest_choices) {
    if (choices_set) {
        throw new ChestBuilderException("Choices have already been set!");
    }
    this->choices = chest_choices;
    choices_set = 1;
    return this;
}


ChestTile* ChestTile::ChestBuilder::build() {
    if (!choices_set) {
        throw new ChestBuilderException("Choices have not been set!");
    }
    return new ChestTile(this->choices);
}