#ifndef MAP_INTERPRETER_H
#define MAP_INTERPRETER_H

#include "../FileInterpreter.h"

class Chest;
class ChestTile;

class MapInterpreter : public FileInterpreter {    
    private:
        const char* path;

        bool loadChestPos(QFList* pos_list, int pos[]);
        ChestTile* loadChest(QFDict* chest_contents);
        void loadChests(QFDict* level_contents, Level::LevelBuilder* level_builder);

        LevelLayer loadMapLayer(QFList* layer_contents);
        Level* loadMapLevel(QFDict* level_contents);
    
    public:
        MapInterpreter(const std::string file_name, const std::string path);
        int load(std::vector<Level*>* levels);
};

#endif // MAP_INTERPRETER_H