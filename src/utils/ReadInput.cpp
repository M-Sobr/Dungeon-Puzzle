#include "ReadInput.h"

#include <iostream>

std::string ReadInput::getUserInput(const char* title) {
    printf("%s", title);
    std::string s;
    std::cin >> s;
    return s;
}

int ReadInput::getNumberChoice(const char* title, std::vector<std::string>* choice_names) {
    printf("%s\n", title);
    int option_count = (int)choice_names->size();
    for (int i=0; i < option_count; i++) {
        printf("%d) %s\n", i+1, choice_names->at(i).c_str());
    }

    std::string s;
    while (true) {
        // Get user input
        printf("> ");
        std::cin >> s;
        int option = atoi(s.c_str());
        if (option > 0 && option <= option_count) {
            printf("\n");
            return option;
        }
    }
}

int ReadInput::getBinaryChoice(const char* title, std::string option_1, std::string option_2) {
    std::vector<std::string> choice_names;
    choice_names.push_back(option_1);
    choice_names.push_back(option_2);
    return ReadInput::getNumberChoice(title, &choice_names);
}