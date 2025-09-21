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

FileReaderErrorCode FileReader::readString(std::string* s) {
    // Read the string
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

FileReaderErrorCode FileReader::readInt(int* i) {
    
    char ch;
    *i = 0;
    while ((ch = this->peekChar()) >= '0' && ch <= '9') {
        *i *= 10;
        *i += ch - '0';
        this->skipChar();
    }
    return FileReaderErrorCode::SUCCESS;
}

FileReaderErrorCode FileReader::readDouble(double* d) {
    char ch;
    *d = 0;
    while ((ch = this->peekChar()) >= '0' && ch <= '9') {
        *d *= 10;
        *d += ch - '0';
        this->skipChar();
    }
    if (this->peekChar() == '.') {
        this->skipChar();
        double frac = 0.1;
        while ((ch = this->peekChar()) >= '0' && ch <= '9') {
            *d += (ch - '0') * frac;
            frac /= 10;
            this->skipChar();
        }
    }
    return FileReaderErrorCode::SUCCESS;
}

FileReaderErrorCode FileReader::readKey(std::string* s) {
    if (this->nextChar() != '"') {
        return FileReaderErrorCode::INVALID_FILE_FORMAT;
    }
    return this->readString(s);
}

QFValue* FileReader::readValue(FileReaderErrorCode* errorCode) {
    QFValue* qf_value;
    char ch = this->nextChar();

    if (ch == '"') {
        std::string s;
        *errorCode = this->readString(&s);
        qf_value = new QFString(s);

    } else if (ch == 'i') {
        int i;
        *errorCode = this->readInt(&i);
        qf_value = new QFInt(i);    
    
    } else if (ch == 'd') {
        double d;
        *errorCode = this->readDouble(&d);
        qf_value = new QFDouble(d);
    
    } else if (ch == '[') {
        qf_value = new QFList();
        *errorCode = this->readList(dynamic_cast<QFList*>(qf_value));
    
    } else if (ch == '{') {
        qf_value = new QFDict();
        *errorCode = this->readDict(dynamic_cast<QFDict*>(qf_value));
    
    } else {
        *errorCode = FileReaderErrorCode::INVALID_FILE_FORMAT;
    }

    return qf_value;
}

FileReaderErrorCode FileReader::readList(QFList* qf_list) {
    // Variable initialisation
    char ch;
    FileReaderErrorCode errorCode;
    QFValue* qf_value;

    // Read qf_pairs and add to dict
    while ((ch = this->peekChar()) != EOF && ch != ']') {
        if (this->peekChar() == ',') {
            return FileReaderErrorCode::INVALID_FILE_FORMAT;
        }
        qf_value = this->readValue(&errorCode);
        if (errorCode != FileReaderErrorCode::SUCCESS) {
            return errorCode;
        }
        qf_list->addValue(qf_value);
        if (this->peekChar() == ',') {
            this->skipChar();
        }
    }
    this->skipChar();

    // Return success if everything is successful
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
        qf_pair = this->readPair(&errorCode);
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

QFPair* FileReader::readPair(FileReaderErrorCode* errorCode) {
    std::string key;
    QFPair* qf_pair = nullptr;

    // Get the key
    *errorCode = this->readKey(&key);
    if (*errorCode != FileReaderErrorCode::SUCCESS) {
        return qf_pair;
    }

    // Check that the key and value are separated by a colon
    if (this->nextChar() != ':') {
        return qf_pair;
    }

    // Get the value
    QFValue* value = this->readValue(errorCode);
    if (*errorCode != FileReaderErrorCode::SUCCESS) {
        return qf_pair;
    }

    qf_pair = new QFPair(key, value);
    *errorCode = FileReaderErrorCode::SUCCESS;
    return qf_pair;
}

FileReaderErrorCode FileReader::readFile(QFDict* qf_dict) {    
    if (!file_data) {
        return FileReaderErrorCode::INVALID_FILE;
    }
    return this->readDict(qf_dict);
}
