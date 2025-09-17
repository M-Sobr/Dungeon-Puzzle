#include "FileReader.h"
#include "qf_types/QFTypes.h"

FileReader::FileReader(char filename[]) : file_data(filename) {
}

FileReaderErrorCode FileReader::readFile(QFDict* qf_dict) {    
    if (!file_data) {
        return FileReaderErrorCode::EMPTY_OR_INVALID_FILE;
    }
    
    char ch;
    while (ch != EOF) {
        ch = (char)file_data.get();
        printf("%c", ch);
    }
    printf("\n");
    return FileReaderErrorCode::SUCCESS;
}
