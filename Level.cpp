#include <iostream>
#include <string>

class Level {
    private:
        std::string level;

    public:
        Level(char level_string[1000]) {
            level = level_string;
        }
    
        void printLevel() {
            std::cout << level;
        }
};