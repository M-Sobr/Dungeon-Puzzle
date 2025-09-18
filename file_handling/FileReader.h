#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <fstream>

class QFDict;
class QFPair;

/** Contains the possible results of reading a file */
enum FileReaderErrorCode {
    SUCCESS,
    INVALID_FILE
};

class FileReader {
    private:
        std::ifstream file_data;

        /** Get the next character from the file, ignoring blanks. */
        char getNextChar();

        /** Fill in the following QFPair from the file details */
        FileReaderErrorCode readPair(QFPair* qf_pair);

        /** Fill in the following QFDict from the file details */
        FileReaderErrorCode readDict(QFDict* qf_dict);

    public:
        /** Read a file and store it in a new QFDict. 
         *  - Output corresponds to the result of the operation.
        */
        FileReaderErrorCode readFile(QFDict* qf_dict);


        FileReader(char filename[]);
};

#endif // FILE_READER_H