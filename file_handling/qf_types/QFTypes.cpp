#include "QFTypes.h"

QFValue::QFValue(QFTypes type) {
    this->value_type = type;
}

QFPair::QFPair(std::string k, QFValue* v) {
    this->key = k;
    this->value = v;
}

QFString::QFString(std::string v) : QFValue::QFValue(QFTypes::QF_STRING) {
    this->value = v;
}

QFInt::QFInt(int v) : QFValue::QFValue(QFTypes::QF_INT) {
    this->value = v;
}

QFList::QFList() : QFValue::QFValue(QFTypes::QF_LIST) {
}

QFDict::QFDict() : QFValue::QFValue(QFTypes::QF_DICT) {
}