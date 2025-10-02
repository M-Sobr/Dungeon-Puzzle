#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <map>

#define MAX_LEVEL_NAME_LENGTH 20
#define MAX_LEVEL_CHARACTERS 1000

#define MAX_LEVEL_ROWS 10
#define MAX_LEVEL_COLS 12

class Tile;
class SpecialTile;

class LevelLayer {
    private:
        /** Fill blanks in ([0:rows-2], [cols:new_cols-1]) inclusive */
        void fillBlanks(int new_cols);

        int isValidChar(char c);
    
    public:
        char contents[MAX_LEVEL_ROWS][MAX_LEVEL_COLS];
        int rows;
        int cols;

        LevelLayer();
        void addRow(std::string row_string);
};

class Level {
    private:
        std::string name;

        std::vector<LevelLayer> layout_layers;
        int currentLayerIndex;
        LevelLayer currentLayer;

        int player_pos[2];
        char symbolUnderPlayer;

        int objective_tiles;
        std::map<int*, SpecialTile*>* special_tiles;
        bool level_beaten;

        /** Create a new level with a name, layers, player_pos (row, col) and objective tiles. */
        Level(std::string level_name, std::vector<LevelLayer> layout_layers, std::map<int*, SpecialTile*>* special_tiles, int* player_pos, int start_layer, int objective_tiles);

        

        bool tileOutsideLevel(int row, int col);
        bool tileIsWall(int row, int col);
    
    public:
        Level();
        
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

        class LevelBuilder {
            private:
                // Necessary fields
                std::string level_name;
                std::vector<LevelLayer> layout_layers;
                int player_pos[2];
                int start_layer;
                int objective_tiles;
                int finish_tiles;
                std::map<int*, SpecialTile*>* special_tiles;

                // A counter to make sure every level field required is set before building
                int necessary_fields_set;
                
                /** Adds the player to the game. Returns true if player adding is successful and
                 *   false if player has already been added.
                 */
                bool addPlayer(int row, int col, int layer);

            public:
                LevelBuilder();
                
                Level::LevelBuilder* setName(std::string name);
                
                Level::LevelBuilder* addLayer(LevelLayer layer);

                Level::LevelBuilder* addSpecialTile(int* pos[3], SpecialTile* tile);

                /** Builds the level if all required fields have been set */
                Level* build();

        };
};

#endif