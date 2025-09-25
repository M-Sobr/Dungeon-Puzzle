#ifndef ACTION_H
#define ACTION_H

class Level;
class Player;
class PastAction;

enum ActionType {
    MOVE_UP,
    MOVE_RIGHT,
    MOVE_DOWN,
    MOVE_LEFT,
    UNDO,
    EXIT,
    RESET,
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
        static Action fromText(const char text[]);
        ActionType getType();
        PastAction* resolveAction(Level* level, Player* player);
        
};

#endif;