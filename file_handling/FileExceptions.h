#ifndef FILE_EXCEPTIONS_H
#define FILE_EXCEPTIONS_H

#include <exception>
#include <string>

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

class InvalidMapLevelException : public std::exception {
    private:
        std::string msg;
    
    public:
    InvalidMapLevelException(const std::string msg);
        const char* what();
};  

class InvalidPlayerLevelException : public std::exception {
    private:
        std::string msg; 

    public:
        InvalidPlayerLevelException(const std::string msg);
        const char* what();
};

class NullPointerException : public std::exception {
    private:
        std::string msg;
    
    public:
    NullPointerException(const std::string msg);
        const char* what();
};  

#endif