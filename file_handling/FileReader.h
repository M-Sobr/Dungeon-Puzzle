#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <fstream>

class QFDict;
class QFPair;
class QFValue;
class QFList;

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
        void readString(std::string* string);

        /** Fill in the following int from the file details */
        void readInt(int* value);

        /** Fill in the following double from the file details */
        void readDouble(double* value);

        /** Fill in the following empty string from file details */
        void readKey(std::string* string);

        /** Fill in the following QFValue from file details */
        QFValue* readValue();

        /** Fill in the following QFPair from the file details */
        QFPair* readPair();

        /** Fill in the following QFList from the file details */
        void readList(QFList* qf_list);

        /** Fill in the following QFDict from the file details */
        void readDict(QFDict* qf_dict);

    public:
        /** Read a file and store it in a new QFDict. */
        void readFile(QFDict* qf_dict);


        FileReader(char filename[]);
        ~FileReader();
};

#endif // FILE_READER_H