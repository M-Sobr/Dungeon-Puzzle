#include "FileExceptions.h"

InvalidFileException::InvalidFileException(const char* m) {
    this->msg = m;
}

const char* InvalidFileException::what() {
    return msg.c_str();
}

InvalidFileFormatException::InvalidFileFormatException(const char* m) {
    this->msg = m;
}

const char* InvalidFileFormatException::what() {
    return msg.c_str();
}