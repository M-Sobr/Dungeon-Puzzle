#ifndef ACTION_H
#define ACTION_H

#include "../level/Level.h"
#include "Player.h"

enum ActionType {
    MOVE_UP,
    MOVE_RIGHT,
    MOVE_DOWN,
    MOVE_LEFT,
    EXIT,
    NULL_ACTION
};

class Action {
    private:
        ActionType type; 
        Action(ActionType type);
        int row_direction;
        int col_direction;
    
    public:
        // Return true if this action involves moving the player.
        bool involvesMovement(); 
        static Action fromText(char text[]);
        ActionType getType();
        void resolveAction(Level level, Player player);
    
};

#endif;