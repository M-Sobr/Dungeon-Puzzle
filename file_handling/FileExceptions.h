#ifndef FILE_EXCEPTIONS_H
#define FILE_EXCEPTIONS_H

#include <exception>
#include <string>
#include <queue>

class InvalidFileException : public std::exception {
    private:
        std::string msg;
    
    public:
    InvalidFileException(const std::string msg);
        const char* what();
};  

class InvalidFileFormatException : public std::exception {
    private:
        std::string msg;
    
    public:
        InvalidFileFormatException(const std::string msg);
        const char* what();
};  

class FileInterpreterException : public std::exception {
    private:
        std::string msg;
    
    public:
        FileInterpreterException(const std::string msg);
        const char* what();
};

class FileInterpreterExceptionList : public std::exception {
    private:
        std::queue<FileInterpreterException> msg;
    
    public:
        FileInterpreterExceptionList();
        const char* what();
};

class InvalidMapLevelException : public FileInterpreterException {
    public:
        InvalidMapLevelException(const std::string msg);
};  

class InvalidPlayerLevelException : public FileInterpreterException {
    public:
        InvalidPlayerLevelException(const std::string msg);
};

class NullPointerException : public FileInterpreterException {
    public:
        NullPointerException(const std::string msg);
};  

#endif