#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <fstream>

class QFDict;
class QFPair;
class QFValue;
class QFList;

/** Contains the possible results of reading a file */
enum FileReaderErrorCode {
    SUCCESS,
    INVALID_FILE,
    INVALID_FILE_FORMAT
};

class FileReader {
    private:
        std::ifstream file_data;
        char currentChar;

        /** Look at the next character from the file, ignoring blanks. */
        char peekChar();

        /** Skip past the current character in the file without returning it, ignoring blanks. */
        void skipChar();
        
        /** Get the next character from the file, ignoring blanks. */
        char nextChar();

        /** Fill in the following string from the file details */
        FileReaderErrorCode readString(std::string* string);

        /** Fill in the following int from the file details */
        FileReaderErrorCode readInt(int* value);

        /** Fill in the following double from the file details */
        FileReaderErrorCode readDouble(double* value);

        /** Fill in the following empty string from file details */
        FileReaderErrorCode readKey(std::string* string);

        /** Fill in the following QFValue from file details */
        FileReaderErrorCode readValue(QFValue* qf_value);

        /** Fill in the following QFPair from the file details */
        FileReaderErrorCode readPair(QFPair* qf_pair);

        /** Fill in the following QFList from the file details */
        FileReaderErrorCode readList(QFList* qf_list);

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