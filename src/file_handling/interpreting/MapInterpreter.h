#ifndef MAP_INTERPRETER_H
#define MAP_INTERPRETER_H

#include "../FileInterpreter.h"

class MapInterpreter : public FileInterpreter {    
    private:
        const char* path;
    
        LevelLayer loadMapLayer(QFList* layer_contents);
        void loadChests(QFDict* level_contents, Level::LevelBuilder* level_builder);
        Level* loadMapLevel(QFDict* level_contents);
    
    public:
        MapInterpreter(const std::string file_name, const std::string path);
        int load(std::vector<Level*>* levels);
};

#endif // MAP_INTERPRETER_H