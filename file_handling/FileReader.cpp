#include "FileReader.h"
#include "qf_types/QFTypes.h"

FileReader::FileReader(char filename[]) : file_data(filename) {
}

FileReaderErrorCode FileReader::readFile(QFDict* qf_dict) {
    char txt[20];
    file_data.getline(txt, 20);
    printf("\nLine 1: %s\n", txt);
    return FileReaderErrorCode::SUCCESS;
}