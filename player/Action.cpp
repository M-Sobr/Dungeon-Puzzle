#include "Action.h"
#include "PastAction.h"
#include "../utils/Utils.h"
#include "../level/Tile.h"
#include "../level/Level.h"
#include "Player.h"

Action Action::fromText(const char text[]) {
    if (equalsIgnoreCase(text[0], 'w')) {
        return Action::Action(ActionType::MOVE_UP);
    } else if (equalsIgnoreCase(text[0], 'a')) {
        return Action::Action(ActionType::MOVE_LEFT);
    } else if (equalsIgnoreCase(text[0], 's')) {
        return Action::Action(ActionType::MOVE_DOWN);
    } else if (equalsIgnoreCase(text[0], 'd')) {
        return Action::Action(ActionType::MOVE_RIGHT);
    } else if (equalsIgnoreCase(text[0], 'z')) {
        return Action::Action(ActionType::UNDO);
    } else if (equalsIgnoreCase(text[0], 'r')) {
        return Action::Action(ActionType::RESET);
    } else if (equalsIgnoreCase(text, "exit", 4)) {
        return Action::Action(ActionType::EXIT);
    } else {
        return Action::Action(ActionType::NULL_ACTION);
    }
}

Action::Action(ActionType actionType) : type(actionType) {
    
    // Fill in direction of the action from its type.
    switch (actionType) {
        case ActionType::MOVE_UP:
            row_direction = -1;
            col_direction = 0;
            break;
        case ActionType::MOVE_RIGHT:
            row_direction = 0;
            col_direction = 1;
            break;
        case ActionType::MOVE_DOWN:
            row_direction = 1;
            col_direction = 0;
            break;
        case ActionType::MOVE_LEFT:
            row_direction = 0;
            col_direction = -1;
            break;
        default:
            row_direction = 0;
            col_direction = 0;                
    }
}

bool Action::involvesMovement() {
    return (row_direction || col_direction);
}

ActionType Action::getType() {
    return type;
}

PastAction* Action::resolveAction(Level* level, Player* player) {
    // Initialise variables
    int prev_pos[2];
    level->getPlayerPos(prev_pos);
    Tile* tile = new NullTile(PLAYER_TILE);
    
    // Do action components relevant to movement
    if (this->involvesMovement()) {
        int destination[2];
        
        int move_count = level->calculateMovementDestination(&destination[0], &destination[1],
            this->row_direction, this->col_direction, player->getMovement());
        
        if (move_count) {
            
            tile = level->getTileAtPosition(destination[0], destination[1]);
            level->movePlayerTo(destination[0], destination[1]);
            player->applyEffect(new Effect(EffectTypes::TAKE_DAMAGE, move_count));
            tile->resolveEffects(player);          
        }
    }
    int effect_count = player->effect_counter;
    player->effect_counter = 0;
    return new PastAction(prev_pos[0], prev_pos[1], tile, effect_count);
}

PastAction::PastAction(int prev_row, int prev_col, Tile* tile, int effect_count) :
    prev_row_pos(prev_row), prev_col_pos(prev_col), tile_at_pos(tile), effects_applied_count(effect_count) {
        
    ;
}

PastAction::~PastAction() {
    delete tile_at_pos;
}

void PastAction::undoAction(Level* level, Player* player) {
    level->resetPlayerTo(this->prev_row_pos, this->prev_col_pos, this->tile_at_pos);
    for (int i=0; i < this->effects_applied_count; i++) {
        player->undoEffect();
    }
}