#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>

#define MAX_LEVEL_NAME_LENGTH 20
#define MAX_LEVEL_CHARACTERS 1000

#define MAX_LEVEL_ROWS 10
#define MAX_LEVEL_COLS 12

class Level {
    private:
        char name[MAX_LEVEL_NAME_LENGTH];
        char contents[MAX_LEVEL_ROWS][MAX_LEVEL_COLS];
        int rows;
        int cols;

    public:
        Level();
        Level(char level_name[], char level_string[], int level_rows, int level_cols);
        void printLevel();
        void printName();
        int getRowCount();
        int getColCount();
        char getPosition(int row, int col);
};

int loadLevels(Level* levels);

#endif