#include "FileReader.h"
#include "qf_types/QFTypes.h"

FileReader::FileReader(char filename[]) {
    file_data = std::ifstream(filename);
}

FileReaderErrorCode FileReader::readFile(QFDict* qf_dict) {
    return FileReaderErrorCode::SUCCESS;
}