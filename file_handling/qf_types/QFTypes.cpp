#include "QFTypes.h"
#include "../FileExceptions.h"

QFValue::QFValue(QFTypes type) : value_type(type) {
    ;
}

template<class V>
V* QFValue::get(const std::string errorMessage) {
    V* value = dynamic_cast<V*>(this);
    if (value == nullptr) {
        throw new NullPointerException(errorMessage);
    }
    return value;
}

QFPair::QFPair(std::string k, QFValue* v) : 
    key(k), value(v) {
    
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

QFString::QFString(std::string v) : 
    QFValue::QFValue(QFTypes::QF_STRING), value(v) {
    
    ;
}

std::string QFString::getValue() {
    if (this == nullptr) {
        throw new NullPointerException("This QFString is null!");
    }
    return this->value;
}

QFInt::QFInt(int v) : 
    QFValue::QFValue(QFTypes::QF_INT), value(v) {
    ;
}

int QFInt::getValue() {
    if (this == nullptr) {
        throw new NullPointerException("This QFInt is null!");
    }
    return this->value;
}

QFDouble::QFDouble(double v) :
    QFValue::QFValue(QFTypes::QF_DOUBLE), value(v) {
    ;
}

double QFDouble::getValue() {
    if (this == nullptr) {
        throw new NullPointerException("This QFDouble is null!");
    }
    return this->value;
}

QFList::QFList() : QFValue::QFValue(QFTypes::QF_LIST) {
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

QFDict::QFDict() : QFValue::QFValue(QFTypes::QF_DICT) {
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
    QFValue f = QFValue::QFValue(QF_VALUE);
    f.get<QFString>("");
    f.get<QFList>("");
    f.get<QFDict>("");
    f.get<QFInt>("");
}