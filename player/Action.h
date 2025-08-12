#ifndef ACTION_H
#define ACTION_H

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
    
    public:
        //Action(ActionType type);    
        static Action fromText(char text[]);
        ActionType getType();
    
};

#endif;