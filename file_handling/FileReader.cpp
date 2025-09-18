#include "FileReader.h"
#include "qf_types/QFTypes.h"
#include "../utils/Utils.h"

FileReader::FileReader(char filename[]) : file_data(filename) {
}

char FileReader::getNextChar() {
    char ch;
    do {
        ch = (char)file_data.get();
    } while (isBlank(ch));
    
    return ch;
}

FileReaderErrorCode FileReader::readPair(QFPair* qf_pair) {
    return FileReaderErrorCode::SUCCESS;
}

FileReaderErrorCode FileReader::readDict(QFDict* qf_dict) {
    char ch;
    while ((ch = this->getNextChar()) != '}' && ch != EOF) {
        printf("%c", ch);
    }
    return FileReaderErrorCode::SUCCESS;
}

FileReaderErrorCode FileReader::readFile(QFDict* qf_dict) {    
    if (!file_data) {
        return FileReaderErrorCode::INVALID_FILE;
    }
    return this->readDict(qf_dict);
}
