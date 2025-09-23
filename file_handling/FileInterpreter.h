#ifndef FILE_INTERPRETER_H
#define FILE_INTERPRETER_H

#include <set>
#include <vector>

class Level;
class QFPair;
class QFDict;
class QFList;
class LevelLayer;

class FileInterpreter {
    private:

        static LevelLayer loadLayer(QFList* layer_contents);
        static Level* loadLevel(QFDict* level_info);
        
    public:

        /** Load the levels from the required file into the provided array
         * - Returns the number of levels in the game. 
        */
        static int loadLevels(std::vector<Level*>* levels);

        
};


#endif  // FILE_INTERPRETER_H