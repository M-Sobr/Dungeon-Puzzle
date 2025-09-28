#ifndef FILE_INTERPRETER_H
#define FILE_INTERPRETER_H

#include "FileExceptions.h"

#include <set>
#include <vector>

class Level;
class QFPair;
class QFDict;
class QFList;
class LevelLayer;
class LevelUpEffects;
class Effect;
class EffectsList;

class FileInterpreter {
    private:

        FileInterpreterExceptionList* exceptions;

        LevelLayer loadMapLayer(QFList* layer_contents);
        Level* loadMapLevel(QFDict* level_info);

        Effect* loadEffect(QFPair* effect_info);
        EffectsList* loadEffectsList(QFDict* effects_list_info);
        
        std::vector<EffectsList*> loadPlayerLevel(QFList* level_effects_list);
        
        FileInterpreter(const std::string file_name);
        void addException(FileInterpreterException* e);
        FileInterpreterExceptionList* getExceptionList();

    public:

        /** Load the map levels from the required file into the provided array
         * - Returns the number of levels in the game. 
        */
        static int loadMapLevels(std::vector<Level*>* levels);

        /** Load the player levels from the required file into the provided array.
         */
        static void loadPlayerLevels(LevelUpEffects* level_up_effects);

        
};


#endif  // FILE_INTERPRETER_H