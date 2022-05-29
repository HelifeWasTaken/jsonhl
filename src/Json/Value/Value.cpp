/**
 * File              : Value.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include "JsonhlValue.hpp"

jsonhl::Value::Value(const double &value) : _value(value), _type(jsonhl::Value::ValueType::DOUBLE)
{
}
jsonhl::Value::Value(const int &value)
{
    *this = Value(static_cast<double>(value));
}
jsonhl::Value::Value(const bool &value) : _value(value), _type(jsonhl::Value::ValueType::BOOL)
{
}
jsonhl::Value::Value(const std::string &value) : _value(value), _type(jsonhl::Value::ValueType::STRING)
{
}
jsonhl::Value::Value(const jsonhl::Value::Array &value) : _value(value), _type(jsonhl::Value::ValueType::ARRAY)
{
}
jsonhl::Value::Value(const jsonhl::Value::Object &value) : _value(value), _type(jsonhl::Value::ValueType::OBJECT)
{
}
jsonhl::Value::Value() : _value(nullptr), _type(jsonhl::Value::ValueType::JSONNULL)
{
}

jsonhl::Value::~Value()
{
}
