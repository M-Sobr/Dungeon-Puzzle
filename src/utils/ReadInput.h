#ifndef READ_INPUT_H
#define READ_INPUT_H

#include <string>
#include <vector>

class ReadInput {
    public:
        static std::string getUserInput(const char* title);
        static int getNumberChoice(const char* title, std::vector<std::string>* choice_names);
        static int getBinaryChoice(const char* title, std::string option_1, std::string option_2);
};


#endif // READ_INPUT_H