#include "QFTypes.h"

QFValue::QFValue(QFTypes type) : value_type(type) {
    ;
}

QFPair::QFPair(std::string k, QFValue* v) : 
    key(k), value(v) {
    
    ;
}

std::string QFPair::getKey() {
    return this->key;
}

QFValue* QFPair::getValue() {
    return this->value;
}

QFString::QFString(std::string v) : 
    QFValue::QFValue(QFTypes::QF_STRING), value(v) {
    
    ;
}

QFInt::QFInt(int v) : 
    QFValue::QFValue(QFTypes::QF_INT), value(v) {
    ;
}

int QFInt::getValue() {
    if (this == nullptr) {
        return -1;
    }
    return this->value;
}

QFDouble::QFDouble(double v) :
    QFValue::QFValue(QFTypes::QF_DOUBLE), value(v) {
    ;
}

QFList::QFList() : QFValue::QFValue(QFTypes::QF_LIST) {
    ;
}

void QFList::addValue(QFValue* value) {
    this->values.push_back(value);
}

std::vector<QFValue*> QFList::getValues() {
    return this->values;
}

QFDict::QFDict() : QFValue::QFValue(QFTypes::QF_DICT) {
    ;
}

void QFDict::addPair(QFPair* pair) {
    this->pairs.push_back(pair);
}

std::vector<QFPair*> QFDict::getPairs() {
    return this->pairs;
}

QFValue* QFDict::getValueFromKey(std::string key) {
    QFPair* qf_pair;
    for (int i=0; i < (this->pairs).size(); i++) {
        qf_pair = (this->pairs)[i];
        if (qf_pair->getKey().compare(key) == 0) {
            return qf_pair->getValue();
        }
    }
    return nullptr;
}