#ifndef FILE_INTERPRETER_H
#define FILE_INTERPRETER_H

#include "FileExceptions.h"
#include "../level/Level.h"

#include <set>
#include <vector>

class QFPair;
class QFDict;
class QFList;
class LevelUpEffects;
class Effect;
class EffectsList;
class EffectChoices;

class FileInterpreter {
    private:

        FileInterpreterExceptionList* exceptions;

        Effect* loadEffect(QFPair* effect_info);
        EffectsList* loadEffectsList(QFDict* effects_list_info);
    
        

        static int inline resolveCorruptedSaveFile();

    protected:
        FileInterpreter(const std::string file_name);    
        void addException(FileInterpreterException* e);
        FileInterpreterExceptionList* getExceptionList();

        EffectChoices* loadEffectChoices(QFList* effect_choices);

    public:
        virtual ~FileInterpreter() {}


        /** Load the map levels from the required file into the provided array
         * - Returns the number of levels in the game. 
        */
        static int loadMapLevels(std::vector<Level*>* levels);

        /** Load the player levels from the required file into the provided array.
         */
        static void loadPlayerLevels(LevelUpEffects* level_up_effects);

        static int loadSaveFile(const char* save_name);

        static void updateSaveFile(const char* save_name, int current_level);

        static void deleteSaveFile(const char* save_name);

        
};


#endif  // FILE_INTERPRETER_H