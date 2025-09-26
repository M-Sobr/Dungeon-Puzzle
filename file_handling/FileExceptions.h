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
        const std::string msg;
        const int start_line;
        const int end_line;
    
    public:
        FileInterpreterException(const std::string msg, const int start_line, const int end_line);
        const std::string generateMessage(const std::string msg, const int start_line, const int end_line);
        const char* what();
};

class FileInterpreterExceptionList : public std::exception {
    private:
        std::queue<FileInterpreterException*> exceptions;
    
    public:
        FileInterpreterExceptionList();
        void operator+=(FileInterpreterException* e);
        const char* what();
};

class InvalidMapLevelException : public FileInterpreterException {
    public:
        InvalidMapLevelException(const std::string msg, const int start_line, const int end_line);
};  

class InvalidPlayerLevelException : public FileInterpreterException {
    public:
        InvalidPlayerLevelException(const std::string msg, const int start_line, const int end_line);
};

class NullPointerException : public FileInterpreterException {
    public:
        NullPointerException(const std::string msg);    
        NullPointerException(const std::string msg, const int start_line, const int end_line);
};  

#endif