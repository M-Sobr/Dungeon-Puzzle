#include "FileReader.h"
#include "qf_types/QFTypes.h"
#include "../utils/Utils.h"
#include "FileExceptions.h"

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

void FileReader::readString(std::string* s) {
    // Read the string
    char ch;
    while ((ch = this->peekChar()) != '"' && ch != EOF) {
        s->push_back(ch);
        this->currentChar = (char)file_data.get();
    }
    
    // Check if the string finishing was successful
    if (ch == EOF) {
        return;
    } else {
        this->skipChar();
        return;
    }
}

void FileReader::readInt(int* i) {
    
    char ch;
    *i = 0;
    
    // Check for negative
    int negative = 0;
    if (this->peekChar() == '-') {
        negative = 1;
        this->skipChar();
    }

    while ((ch = this->peekChar()) >= '0' && ch <= '9') {
        *i *= 10;
        *i += ch - '0';
        this->skipChar();
    }

    if (negative) {
        *i = -(*i);
    }

    return;
}

void FileReader::readDouble(double* d) {
    char ch;
    *d = 0;
    
    // Check for negative
    int negative = 0;
    if (this->peekChar() == '-') {
        negative = 1;
        this->skipChar();
    }

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

    if (negative) {
        *d = -(*d);
    }

    return;
}

void FileReader::readKey(std::string* s) {
    if (this->nextChar() != '"') {
        return;
    }
    return this->readString(s);
}

QFValue* FileReader::readValue() {
    QFValue* qf_value;
    char ch = this->nextChar();

    if (ch == '"') {
        std::string s;
        this->readString(&s);
        qf_value = new QFString(s);

    } else if (ch == 'i') {
        int i;
        this->readInt(&i);
        qf_value = new QFInt(i);    
    
    } else if (ch == 'd') {
        double d;
        this->readDouble(&d);
        qf_value = new QFDouble(d);
    
    } else if (ch == '[') {
        qf_value = new QFList();
        this->readList(dynamic_cast<QFList*>(qf_value));
    
    } else if (ch == '{') {
        qf_value = new QFDict();
        this->readDict(dynamic_cast<QFDict*>(qf_value));
    
    } else {
        qf_value = nullptr;
    }

    return qf_value;
}

void FileReader::readList(QFList* qf_list) {
    // Variable initialisation
    char ch;
    QFValue* qf_value;

    // Read qf_pairs and add to dict
    while ((ch = this->peekChar()) != EOF && ch != ']') {
        if (this->peekChar() == ',') {
            return;
        }
        qf_value = this->readValue();
        qf_list->addValue(qf_value);
        if (this->peekChar() == ',') {
            this->skipChar();
        }
    }
    this->skipChar();

    // Return success if everything is successful
    return;
}

void FileReader::readDict(QFDict* qf_dict) {
    // Variable initialisation
    char ch;
    QFPair* qf_pair;

    // Read qf_pairs and add to dict
    while ((ch = this->peekChar()) != EOF && ch != '}') {
        if (this->peekChar() == ',') {
            return;
        }
        qf_pair = this->readPair();
        qf_dict->addPair(qf_pair);
        if (this->peekChar() == ',') {
            this->skipChar();
        }
    }
    this->skipChar();

    // Return success if everything is successful
    return;
}

QFPair* FileReader::readPair() {
    std::string key;
    QFPair* qf_pair = nullptr;

    // Get the key
    this->readKey(&key);

    // Check that the key and value are separated by a colon
    if (this->nextChar() != ':') {
        return qf_pair;
    }

    // Get the value
    QFValue* value = this->readValue();

    qf_pair = new QFPair(key, value);
    return qf_pair;
}

void FileReader::readFile(QFDict* qf_dict) {    
    if (!file_data) {
        throw new InvalidFileException("File selected has no data!");
    }
    this->readDict(qf_dict);
}
