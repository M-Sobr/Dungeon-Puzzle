#ifndef FILE_INTERPRETER_H
#define FILE_INTERPRETER_H

class Level;

class FileInterpreter {
    public:
        
        /** Load the levels from the required file into the provided array
         * - Returns the number of levels in the game. 
        */
        static int loadLevels(Level* levels);
};


#endif  // FILE_INTERPRETER_H