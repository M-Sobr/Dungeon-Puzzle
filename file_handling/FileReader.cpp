#include "FileReader.h"

FileReader::FileReader(char filename[]) {
    file_data = std::ifstream(filename);
}