#include "PlayerInterpreter.h"
#include "../qf_types/QFTypes.h"
#include "../FileReader.h"
#include "../../effect/LevelUpEffects.h"

PlayerInterpreter::PlayerInterpreter(const std::string file_name, const std::string p) : 
    FileInterpreter::FileInterpreter(file_name), path(p.c_str()) {
    ;
}

void PlayerInterpreter::load(LevelUpEffects* level_up_effects) {
    try {
        // Intialise variables and read file
        FileReader level_file_reader(this->path);
        QFDict level_file_contents(1);
        level_file_reader.readFile(&level_file_contents);

        // Get dict of player levels
        QFDict* player_levels_dict;
        try {
            player_levels_dict = level_file_contents.getValueFromKey("Player Levels")->
                get<QFDict>("No QFDict in a \"Player Levels\" key found.");
        
        } catch (FileInterpreterException* e) {
            this->addException(e);
            throw this->getExceptionList();
        
        } catch (NoKeyFoundException* e) {
            this->addException(new InvalidMapLevelException(e->what(), 
                level_file_contents.getStartLine(), level_file_contents.getEndLine()));
            throw this->getExceptionList();
        }

        // Get list of player level effects
        QFList* player_effects_list;
        try {
            player_effects_list = player_levels_dict->getValueFromKey("Effects")->
                get<QFList>("No QFList in a \"Effects\" key found.");
        
        } catch (FileInterpreterException* e) {
            this->addException(e);
            throw this->getExceptionList();
        
        } catch (NoKeyFoundException* e) {
            this->addException(new InvalidMapLevelException(e->what(), 
                player_levels_dict->getStartLine(), player_levels_dict->getEndLine()));
            throw this->getExceptionList();     
        }


        *level_up_effects = LevelUpEffects::LevelUpEffects();

        for (QFValue* list : player_effects_list->getValues()) {
            try {
                level_up_effects->addLevel(this->loadEffectChoices(list->get<QFList>("Player level effects list is not QFList!")));
            } catch (FileInterpreterException* e) {
                this->addException(e);
            }
        }

        FileInterpreterExceptionList* exceptionList = this->getExceptionList();
        if (exceptionList->size() > 0) {
            throw exceptionList;
        }

    } catch (FileInterpreterExceptionList* e) {
        throw e;
    } catch (InvalidFileException* e) {
        throw e;
    } catch (InvalidFileFormatException* e) {
        throw e;
    }
}