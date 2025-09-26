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

FileInterpreterException::FileInterpreterException(const std::string m, const int start, const int end) :
   msg(generateMessage(m, start, end)), start_line(start), end_line(end) {
;
}

const std::string FileInterpreterException::generateMessage(const std::string m, const int start, const int end) {
    char c[100];
    std::string message;

    if (start == end) {
        sprintf_s(c, "Line %d: %s", start, m.c_str());
    
    } else {
        sprintf_s(c, "Line %d-%d: %s", start, end, m.c_str());
    }

    message.append(c);
    return message;
}

const char* FileInterpreterException::what() {
    return msg.c_str();
}

FileInterpreterExceptionList::FileInterpreterExceptionList() {
    ;
}

void FileInterpreterExceptionList::operator+=(FileInterpreterException* e) {
    this->exceptions.push(e);
}

const char* FileInterpreterExceptionList::what() {
    return "temp";
}

InvalidMapLevelException::InvalidMapLevelException(const std::string m, const int start_line, const int end_line) :
    FileInterpreterException::FileInterpreterException(m, start_line, end_line) {
    ;   
}

InvalidPlayerLevelException::InvalidPlayerLevelException(const std::string m, const int start_line, const int end_line):
    FileInterpreterException::FileInterpreterException(m, start_line, end_line) {
    ;
}

NullPointerException::NullPointerException(const std::string m):
    FileInterpreterException::FileInterpreterException(m, -1, -1) {
    ;
}

NullPointerException::NullPointerException(const std::string m, const int start_line, const int end_line):
    FileInterpreterException::FileInterpreterException(m, start_line, end_line) {
    ;
}