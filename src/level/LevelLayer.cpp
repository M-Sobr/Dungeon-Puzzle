#include "Level.h"
#include "Tile.h"
#include "../file_handling/FileExceptions.h"

std::set<char> valid_chars = {'P', '_', ' ', 'X', '*',
    '#', 
    '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '+'
};

LevelLayer::LevelLayer() :
    rows(0), cols(0) {
    ;
}

void LevelLayer::fillBlanks(int new_cols) {
    for (int i=0; i<rows-1; i++) {
        for (int j=cols; j<new_cols; j++) {
            contents[i][j] = 'X';
        }
        contents[i][new_cols] = '\0';
    }
}

int inline LevelLayer::isValidChar(char c) {
    return (int)valid_chars.count(c);
}

void LevelLayer::addRow(std::string row_string) {
    int row_string_size = (int)row_string.size();
    int j;
    
    // Add to contents
    for (j=0; j < row_string_size; j++) {
        char c = row_string.at(j);
        if (LevelLayer::isValidChar(c)) {
            contents[rows][j] = c;
        } else {
            throw new LevelBuilderException("Invalid level character " + c);
        }
    }
    for (j=row_string_size; j<cols; j++) {
        contents[rows][j] = 'X';
    }

    
    // Update rows and cols
    rows ++;
    if (cols < row_string_size) {
        fillBlanks(row_string_size);
        cols = row_string_size;
    }
    contents[rows-1][cols] = '\0';
}