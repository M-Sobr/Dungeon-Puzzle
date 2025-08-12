#include "Action.h"
#include "../utils/Utils.h"

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
}

ActionType Action::getType() {
    return type;
}