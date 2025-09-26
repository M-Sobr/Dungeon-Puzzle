#include "QFTypes.h"
#include "../FileExceptions.h"

QFEntry::QFEntry(const int start) : 
    start_line(start) {
    ;
}

int inline QFEntry::getStartLine() {
    return this->start_line;
}

void QFEntry::setEndLine(const int end) {
    //printf("Start = %d, End = %d\n", this->start_line, end);  // Temporary
    this->end_line = end;
}

int inline QFEntry::getEndLine() {
    return this->end_line;
}


QFValue::QFValue(const int start_line) : QFEntry(start_line) {
    ;
}

template<class V>
V* QFValue::get(const std::string errorMessage) {
    
    V* value = dynamic_cast<V*>(this);
    if (value == nullptr) {
        throw new NullPointerException(errorMessage, this->getStartLine(), this->getEndLine());
    }
    return value;
}

QFPair::QFPair(std::string k, QFValue* v, const int start_line) : 
    key(k), value(v), QFEntry(start_line) {
    
    ;
}

std::string QFPair::getKey() {
    if (this == nullptr) {
        throw new NullPointerException("This QFDict is null!");
    }
    return this->key;
}

QFValue* QFPair::getValue() {
    if (this == nullptr) {
        throw new NullPointerException("This QFDict is null!");
    }
    return this->value;
}

QFString::QFString(std::string v, const int start_line) : 
    QFValue::QFValue(start_line), value(v) {
    
    ;
}

std::string QFString::getValue() {
    if (this == nullptr) {
        throw new NullPointerException("This QFString is null!");
    }
    return this->value;
}

QFInt::QFInt(int v, const int line) : 
    QFValue::QFValue(line), value(v) {
    
    this->setEndLine(line);
}

int QFInt::getValue() {
    if (this == nullptr) {
        throw new NullPointerException("This QFInt is null!");
    }
    return this->value;
}

QFDouble::QFDouble(double v, const int line) :
    QFValue::QFValue(line), value(v) {
    
    this->setEndLine(line);
}

double QFDouble::getValue() {
    if (this == nullptr) {
        throw new NullPointerException("This QFDouble is null!");
    }
    return this->value;
}

QFList::QFList(const int start_line) : QFValue::QFValue(start_line) {
    ;
}

void QFList::addValue(QFValue* value) {
    if (this == nullptr) {
        throw new NullPointerException("This QFList is null!");
    }
    this->values.push_back(value);
}

std::vector<QFValue*> QFList::getValues() {
    if (this == nullptr) {
        throw new NullPointerException("This QFList is null!");
    }
    return this->values;
}

QFDict::QFDict(const int start_line) : QFValue::QFValue(start_line) {
    ;
}

void QFDict::addPair(QFPair* pair) {
    if (this == nullptr) {
        throw new NullPointerException("This QFDict is null!");
    }
    this->pairs.push_back(pair);
}

std::vector<QFPair*> QFDict::getPairs() {
    if (this == nullptr) {
        throw new NullPointerException("This QFDict is null!");
    }
    return this->pairs;
}

QFValue* QFDict::getValueFromKey(std::string key) {
    if (this == nullptr) {
        throw new NullPointerException("This QFDict is null!");
    }
    QFPair* qf_pair;
    for (int i=0; i < (this->pairs).size(); i++) {
        qf_pair = (this->pairs)[i];
        if (qf_pair->getKey().compare(key) == 0) {
            return qf_pair->getValue();
        }
    }
    return nullptr;
}

/** Never call this function */
void IntialiseGenerics() {
    QFValue f = QFValue::QFValue(0);
    f.get<QFString>("");
    f.get<QFList>("");
    f.get<QFDict>("");
    f.get<QFInt>("");
}