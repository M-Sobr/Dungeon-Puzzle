#ifndef PAST_ACTION_H
#define PAST_ACTION_H

class Tile;
class Level;
class Player;

class PastAction {
    private:
        /** The previous row position of the player before this action */
        int prev_row_pos;
        /** The previous column position of the player before this action */
        int prev_col_pos;
        
        /** The tile which was at the position the player moved to */
        Tile* tile_at_pos;
        
        /** The amount of effects applied to the player as a result of this action */
        int effects_applied_count;

    public:
        /** 
         * - prev_row_pos =  The previous row position of the player before this action
         * - prev_col_pos =  The previous column position of the player before this action
         * - tile_at_pos = The tile which was at the position the player moved to
         * - effects_applied_count = The amount of effects applied to the player as a result of this action
         */
        PastAction(int prev_row_pos, int prev_col_pos, Tile* tile_at_pos, int effects_applied_count);

        ~PastAction();

        /** Undo the action represented by this PastAction. */
        void undoAction(Level* level, Player* player);
};

#endif //PAST_ACTION_H