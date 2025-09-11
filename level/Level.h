#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>

#define MAX_LEVEL_NAME_LENGTH 20
#define MAX_LEVEL_CHARACTERS 1000

#define MAX_LEVEL_ROWS 10
#define MAX_LEVEL_COLS 12

class Tile;

class Level {
    private:
        char name[MAX_LEVEL_NAME_LENGTH];
        char contents[MAX_LEVEL_ROWS][MAX_LEVEL_COLS];
        int rows;
        int cols;
        int player_pos[2];
        char symbolUnderPlayer;

        int objective_tiles;
        bool level_beaten;

        bool tileOutsideLevel(int row, int col);
        bool tileIsWall(int row, int col);
    
    public:
        Level();
        Level(char level_name[MAX_LEVEL_NAME_LENGTH], char level_string[MAX_LEVEL_CHARACTERS], int level_rows, int level_cols);
        void printLevel();
        void printName();
        int getRowCount();
        int getColCount();
        void Level::getPlayerPos(int pos_ptr[2]);
        Tile* getTileAtPosition(int row, int col);
        
        // Check if the level has been beaten or not.
        bool isBeaten();

        // Move player to the specified position
        void movePlayerTo(int row, int col);

        // Move the player to the specified position as an undo of a previous move
        void resetPlayerTo(int row, int col, Tile* tile_at_player);

        // Find where the movement should end and put in dest_row and dest_col. Return the number of spaces moved.
        int calculateMovementDestination(int* dest_row, int* dest_col, int row_direction, int col_direction, int movement);
};

int loadLevels(Level* levels);

#endif