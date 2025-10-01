#ifndef PLAYER_INTERPRETER_H
#define PLAYER_INTERPRETER_H

#include "../FileInterpreter.h"

class PlayerInterpreter : public FileInterpreter {    
    private:
        const char* path;    

    public:
        PlayerInterpreter(const std::string file_name, const std::string path);    
        void PlayerInterpreter::load(LevelUpEffects* level_up_effects);
};

#endif // PLAYER_INTERPRETER_H