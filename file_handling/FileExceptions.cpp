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

FileInterpreterException::FileInterpreterException(const std::string m) {
    this->msg = m;
}

const char* FileInterpreterException::what() {
    return msg.c_str();
}

FileInterpreterExceptionList::FileInterpreterExceptionList() {
    ;
}

const char* FileInterpreterExceptionList::what() {
    return "temp";
}

InvalidMapLevelException::InvalidMapLevelException(const std::string m) :
    FileInterpreterException::FileInterpreterException(m) {
    ;   
}

InvalidPlayerLevelException::InvalidPlayerLevelException(const std::string m):
    FileInterpreterException::FileInterpreterException(m) {
    ;
}

NullPointerException::NullPointerException(const std::string m):
    FileInterpreterException::FileInterpreterException(m) {
    ;
}