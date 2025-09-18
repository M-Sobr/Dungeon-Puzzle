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

QFList::QFList() : QFValue::QFValue(QFTypes::QF_LIST) {
    ;
}

QFDict::QFDict() : QFValue::QFValue(QFTypes::QF_DICT) {
    ;
}

void QFDict::addPair(QFPair* pair) {
    pairs.push_back(pair);
}