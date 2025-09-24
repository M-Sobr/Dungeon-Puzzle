#include "FileExceptions.h"

InvalidFileException::InvalidFileException(const std::string m) {
    this->msg = m;
}

const char* InvalidFileException::what() {
    return msg.c_str();
}

InvalidFileFormatException::InvalidFileFormatException(const std::string m) {
    this->msg = m;
}

const char* InvalidFileFormatException::what() {
    return msg.c_str();
}

InvalidLevelException::InvalidLevelException(const std::string m) {
    this->msg = m;
}

const char* InvalidLevelException::what() {
    return msg.c_str();
}

NullPointerException::NullPointerException(const std::string m) {
    this->msg = m;
}

const char* NullPointerException::what() {
    return msg.c_str();
}