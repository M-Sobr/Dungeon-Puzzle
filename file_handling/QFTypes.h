#ifndef QF_TYPES_H
#define QF_TYPES_H

#include <string>
#include <vector>

enum QFTypes {
    QF_VALUE,
    QF_STRING,
    QF_INT,
    QF_LIST,
    QF_DICT
};

/** A generic value which can be handled in files */
class QFValue {
    private:
        QFTypes value_type;

    public:
        QFValue(QFTypes value_type);
};

/** A string which can be a value. */
class QFString: QFValue {
    private:
        std::string value;

    public:
        QFString(std::string value);    
};

/** An integer which can be a value. */
class QFInt: QFValue {
    private:
        int value;
        
    public:
        QFInt(int value);  
};

/** Represents a list of values associated with a key. 
 * These all have the same type. 
*/
class QFList: QFValue {
    private:
        std::vector<QFValue*> values;

    public:
        QFList();    
};

/** Represents a list of key-value pairs. */
class QFDict: QFValue {
    private:
        std::vector<QFPair*> pairs;

    public:
        QFDict();
};

/** Represents a pair of key and value which are a key part of file formats */
class QFPair {
    private:
        std::string key;
        QFValue value;

    public:
        QFPair(std::string key, QFValue value);    
};

#endif // QF_TYPES_H