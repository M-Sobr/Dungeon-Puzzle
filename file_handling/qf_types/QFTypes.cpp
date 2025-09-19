#include "QFTypes.h"

QFValue::QFValue(QFTypes type) : value_type(type) {
    ;
}

QFPair::QFPair(std::string k, QFValue* v) : 
    key(k), value(v) {
    
    ;
}

QFString::QFString(std::string v) : 
    QFValue::QFValue(QFTypes::QF_STRING), value(v) {
    
    ;
}

QFInt::QFInt(int v) : 
    QFValue::QFValue(QFTypes::QF_INT), value(v) {
    ;
}

QFDouble::QFDouble(double v) :
    QFValue::QFValue(QFTypes::QF_DOUBLE), value(v) {
    ;
}

QFList::QFList() : QFValue::QFValue(QFTypes::QF_LIST) {
    ;
}

void QFList::addValue(QFValue* value) {
    values.push_back(value);
}

QFDict::QFDict() : QFValue::QFValue(QFTypes::QF_DICT) {
    ;
}

void QFDict::addPair(QFPair* pair) {
    pairs.push_back(pair);
}