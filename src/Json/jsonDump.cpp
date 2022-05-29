/**
 * File              : jsonDump.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 13.06.2021
 * Last Modified Date: 13.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include "JsonhlValue.hpp"

static int ____M_jsonhl_indentationLevel = 0;

static std::ostream &____M_jsonhl_printPadding(std::ostream &os)
{
    for (auto i = 0; i < ____M_jsonhl_indentationLevel; i++)
    {
        os << "    ";
    }
    return os;
}

static std::ostream &operator<<(std::ostream &os, const jsonhl::Value::Array &array)
{
    std::size_t i = 0;
    jsonhl::Value::ValueType lastType = jsonhl::Value::ValueType::JSONNULL;

    os << "[";
    while (i != array.size())
    {
        os << *array[i];
        lastType = array[i]->getType();
        i++;
        if (i != array.size())
        {
            os << ", ";
            if (lastType == jsonhl::Value::ValueType::OBJECT)
            {
                ____M_jsonhl_printPadding(os) << "\n";
            }
        }
    }
    return os << "]";
}

static std::ostream &operator<<(std::ostream &os, const jsonhl::Value::Object &object)
{
    auto it = object.begin();

    os << "{\n";
    ____M_jsonhl_indentationLevel++;
    while (it != object.end())
    {
        ____M_jsonhl_printPadding(os) << "\"" << it->first << "\": " << *it->second;
        it++;
        if (it != object.end())
            os << ",\n";
    }
    ____M_jsonhl_indentationLevel--;
    return ____M_jsonhl_printPadding(os << "\n") << "}\n";
}

static std::ostream &operator<<(std::ostream &os, const std::string &buf)
{
    os << "\"";
    for (auto i = 0; i < buf.size(); i++)
    {
        switch (buf[i])
        {
        case '\a':
            os << "\\a";
            break;
        case '\b':
            os << "\\b";
            break;
        case '\t':
            os << "\\t";
            break;
        case '\n':
            os << "\\n";
            break;
        case '\v':
            os << "\\v";
            break;
        case '\f':
            os << "\\f";
            break;
        case '\r':
            os << "\\r";
            break;
        default:
            os << buf[i];
            break;
        }
    }
    return os << "\"";
}

std::ostream &operator<<(std::ostream &os, const jsonhl::Value &value)
{
    switch (value.getType())
    {
    case jsonhl::Value::ValueType::ARRAY:
        return os << value.getArray();
    case jsonhl::Value::ValueType::OBJECT:
        return os << value.getObject();
    case jsonhl::Value::ValueType::STRING:
        return os << value.getStr();
    case jsonhl::Value::ValueType::BOOL:
        return os << (value.getBool() ? "true" : "false");
    case jsonhl::Value::ValueType::DOUBLE:
        return os << value.getDouble();
    case jsonhl::Value::ValueType::JSONNULL:
        return os << "null";
    default:
        return os;
    }
}
