#include "Action.h"
#include "../utils/Utils.h"
#include "../level/Tile.h"

Action Action::fromText(char text[]) {
    if (equalsIgnoreCase(text[0], 'w')) {
        return Action::Action(ActionType::MOVE_UP);
    } else if (equalsIgnoreCase(text[0], 'a')) {
        return Action::Action(ActionType::MOVE_LEFT);
    } else if (equalsIgnoreCase(text[0], 's')) {
        return Action::Action(ActionType::MOVE_DOWN);
    } else if (equalsIgnoreCase(text[0], 'd')) {
        return Action::Action(ActionType::MOVE_RIGHT);
    } else if (equalsIgnoreCase(text, "exit", 4)) {
        return Action::Action(ActionType::EXIT);
    } else {
        return Action::Action(ActionType::NULL_ACTION);
    }
}

Action::Action(ActionType actionType) {
    type = actionType;
    
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

void Action::resolveAction(Level* level, Player* player) {
    if (this->involvesMovement()) {
        int destination[2];
        
        int move_count = level->calculateMovementDestination(&destination[0], &destination[1],
            this->row_direction, this->col_direction, player->getMovement());
        
            if (move_count) {
            
            Tile* tile = level->getTileAtPosition(destination[0], destination[1]);
            level->movePlayerTo(destination[0], destination[1]);
            player->takeDamage(move_count);
            tile->resolveEffects(player);          
        }
    }

}