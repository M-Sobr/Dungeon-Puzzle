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

FileReaderErrorCode FileReader::readFile(QFDict* qf_dict) {    
    if (!file_data) {
        return FileReaderErrorCode::INVALID_FILE;
    }
    
    char ch;
    while (ch != EOF) {
        ch = this->getNextChar();
        printf("%c", ch);
    }
    printf("\n");
    return FileReaderErrorCode::SUCCESS;
}
