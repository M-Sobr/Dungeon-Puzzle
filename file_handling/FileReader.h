#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <fstream>

class QFDict;

/** Contains the possible results of reading a file */
enum FileReaderErrorCode {
    SUCCESS,
    INVALID_FILE
};

class FileReader {
    private:
        std::ifstream file_data;

        

    public:
        /** Read a file and store it in a new QFDict. 
         *  - Output corresponds to the result of the operation.
        */
        FileReaderErrorCode readFile(QFDict* qf_dict);


        FileReader(char filename[]);
};

#endif // FILE_READER_H