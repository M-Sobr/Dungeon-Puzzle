#ifndef QF_TYPES_H
#define QF_TYPES_H

#include <string>
#include <vector>

enum QFTypes {
    QF_VALUE,
    QF_STRING,
    QF_INT,
    QF_DOUBLE,
    QF_LIST,
    QF_DICT
};

/** A generic value which can be handled in files */
class QFValue {
    private:
        QFTypes value_type;

    public:
        QFValue(QFTypes value_type);
        virtual ~QFValue() {}
};

/** Represents a pair of key and value which are a key part of file formats */
class QFPair {
    private:
        std::string key;
        QFValue* value;

    public:
        QFPair(std::string key, QFValue* value);   
        std::string getKey();
        QFValue* getValue(); 
};

/** A string which can be a value. */
class QFString: public QFValue {
    private:
        std::string value;

    public:
        QFString(std::string value);    
};

/** An integer which can be a value. */
class QFInt: public QFValue {
    private:
        int value;
        
    public:
        QFInt(int value);  
        
        /** Get the value associated with this QFInt (or -1 if null) */
        int getValue();
};

/** A double which can be a value */
class QFDouble : public QFValue {
    private:
        double value;
    
    public:
        QFDouble(double value);
};

/** Represents a list of values associated with a key. 
 * These all have the same type. 
*/
class QFList: public QFValue {
    private:
        std::vector<QFValue*> values;

    public:
        QFList();    
        void addValue(QFValue* value);
        std::vector<QFValue*> getValues();
};

/** Represents a list of key-value pairs. */
class QFDict: public QFValue {
    private:
        std::vector<QFPair*> pairs;

    public:
        QFDict();
        void addPair(QFPair* pair);
        std::vector<QFPair*> getPairs();
        QFValue* getValueFromKey(std::string key);
};

#endif // QF_TYPES_H