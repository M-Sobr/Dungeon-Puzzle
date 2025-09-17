#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <fstream>

class FileReader {
    private:
        std::ifstream file_data;

    public:
        FileReader(char filename[]);
};

#endif // FILE_READER_H