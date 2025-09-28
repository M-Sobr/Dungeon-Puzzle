#ifndef QF_TYPES_H
#define QF_TYPES_H

#include <string>
#include <vector>

class QFEntry {
    private:
        const int start_line;
        int end_line;
    
    public:
        QFEntry(const int start_line);
        int getStartLine();
        void setEndLine(const int end_line);
        int getEndLine();
        virtual ~QFEntry() {}
};

/** A generic value which can be handled in files */
class QFValue : public QFEntry {
    public:
        QFValue(const int start_line);
        virtual ~QFValue() {}

        template <class V>
        V* get(const std::string errorMessage);
};

/** Represents a pair of key and value which are a key part of file formats */
class QFPair : public QFEntry {
    private:
        std::string key;
        QFValue* value;

    public:
        QFPair(std::string key, QFValue* value, const int start_line);   
        std::string getKey();
        QFValue* getValue(); 
};

/** A string which can be a value. */
class QFString: public QFValue {
    private:
        std::string value;

    public:
        QFString(std::string value, const int start_line);   
        
        std::string getValue();
};

/** An integer which can be a value. */
class QFInt: public QFValue {
    private:
        int value;
        
    public:
        QFInt(int value, const int line);  
        
        /** Get the value associated with this QFInt (or -1 if null) */
        int getValue();
};

/** A double which can be a value */
class QFDouble : public QFValue {
    private:
        double value;
    
    public:
        QFDouble(double value, const int line);

        double getValue();
};

/** Represents a list of values associated with a key. 
 * These all have the same type. 
*/
class QFList: public QFValue {
    private:
        std::vector<QFValue*> values;

    public:
        QFList(const int start_line);    
        void addValue(QFValue* value);
        std::vector<QFValue*> getValues();
};

/** Represents a list of key-value pairs. */
class QFDict: public QFValue {
    private:
        std::vector<QFPair*> pairs;

    public:
        QFDict(const int start_line);
        void addPair(QFPair* pair);
        std::vector<QFPair*> getPairs();
        QFValue* getValueFromKey(std::string key);
};

#endif // QF_TYPES_H