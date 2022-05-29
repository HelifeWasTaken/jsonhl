/**
 * File              : ValueGet.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include "JsonhlValue.hpp"

const jsonhl::Value::ValueType &jsonhl::Value::getType() const
{
    return this->_type;
}
const jsonhl::Value::ValueHolder &jsonhl::Value::getValue() const
{
    return this->_value;
}
const double &jsonhl::Value::getDouble() const
{
    return std::get<double>(this->_value);
}
const std::int64_t jsonhl::Value::getInteger() const
{
    return static_cast<int64_t>(this->getDouble());
}
const bool &jsonhl::Value::getBool() const
{
    return std::get<bool>(this->_value);
}
const std::string &jsonhl::Value::getStr() const
{
    return std::get<std::string>(this->_value);
}
const jsonhl::Value::Object &jsonhl::Value::getObject() const
{
    return std::get<jsonhl::Value::Object>(this->_value);
}
const jsonhl::Value::Array &jsonhl::Value::getArray() const
{
    return std::get<jsonhl::Value::Array>(this->_value);
}
const jsonhl::Value &jsonhl::Value::operator[](const std::string &varName) const
{
    return *this->getObject().at(varName);
}
const jsonhl::Value &jsonhl::Value::operator[](int varIndex) const
{
    return *this->getArray().at(varIndex);
}
