#ifndef FILE_EXCEPTIONS_H
#define FILE_EXCEPTIONS_H

#include <exception>
#include <string>

class InvalidFileException : public std::exception {
    private:
        std::string msg;
    
    public:
    InvalidFileException(const char* msg);
        const char* what();
};  

class InvalidFileFormatException : public std::exception {
    private:
        std::string msg;
    
    public:
        InvalidFileFormatException(const char* msg);
        const char* what();
};  

#endif