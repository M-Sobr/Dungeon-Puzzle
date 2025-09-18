#include "FileReader.h"
#include "qf_types/QFTypes.h"
#include "../utils/Utils.h"

FileReader::FileReader(char filename[]) : file_data(filename) {
    skipChar();
}

char inline FileReader::peekChar() {
    return currentChar;
}


void FileReader::skipChar() {
    do {
        currentChar = (char)file_data.get();
    } while (isBlank(currentChar));
}


char FileReader::nextChar() {
    char ch = currentChar;
    this->skipChar();
    return ch;
}

FileReaderErrorCode FileReader::readKey(std::string* s) {
    // Check for a valid start of string
    if (this->nextChar() != '"') {
        return FileReaderErrorCode::INVALID_FILE_FORMAT;
    }

    // Read the key
    char ch;
    while ((ch = this->peekChar()) != '"' && ch != EOF) {
        s->push_back(ch);
        this->currentChar = (char)file_data.get();
    }
    
    // Check if the string finishing was successful
    if (ch == EOF) {
        return FileReaderErrorCode::INVALID_FILE_FORMAT;
    } else {
        this->skipChar();
        return FileReaderErrorCode::SUCCESS;
    }
}

FileReaderErrorCode FileReader::readValue(QFValue* qf_value) {
    return FileReaderErrorCode::SUCCESS;
}

FileReaderErrorCode FileReader::readDict(QFDict* qf_dict) {
    // Variable initialisation
    char ch;
    FileReaderErrorCode errorCode;
    QFPair* qf_pair;

    // Read qf_pairs and add to dict
    while ((ch = this->peekChar()) != EOF && ch != '}') {
        if (this->peekChar() == ',') {
            return FileReaderErrorCode::INVALID_FILE_FORMAT;
        }
        errorCode = this->readPair(qf_pair);
        if (errorCode != FileReaderErrorCode::SUCCESS) {
            return errorCode;
        }
        qf_dict->addPair(qf_pair);
        if (this->peekChar() == ',') {
            this->skipChar();
        }
    }
    this->skipChar();

    // Return success if everything is successful
    return FileReaderErrorCode::SUCCESS;
}

FileReaderErrorCode FileReader::readPair(QFPair* qf_pair) {
    std::string key;
    FileReaderErrorCode errorCode;

    errorCode = this->readKey(&key);
    printf("\n%s\n", key.c_str());
    if (errorCode != FileReaderErrorCode::SUCCESS) {
        return errorCode;
    }

    while (this->peekChar() != EOF) {
        printf("%c", this->nextChar());
    }
    return FileReaderErrorCode::SUCCESS;
}

FileReaderErrorCode FileReader::readFile(QFDict* qf_dict) {    
    if (!file_data) {
        return FileReaderErrorCode::INVALID_FILE;
    }
    return this->readDict(qf_dict);
}
