/**
 * File              : DeserializerGet.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 10.06.2021
 * Last Modified Date: 10.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include "JsonhlDeserializer.hpp"

const bool jsonhl::Deserializer::____MgetArray(jsonhl::Value &actualNode, std::string::iterator &it) const
{
    std::size_t i = 0;
    double indexArray = 0;

    if (actualNode.getType() != jsonhl::Value::ARRAY)
        return false;
    if (std::isdigit(*it) == false)
        throw std::runtime_error("Digit array getter is wrongly formatted");
    indexArray = std::stoi(it.base());
    for (; *it; it++)
    {
        if (*it == ']')
            break;
        if (std::isdigit(*it) == false)
            throw std::runtime_error("Digit array getter is wrongly formatted");
    }
    if (*it == '\0')
        throw std::runtime_error("Digit array getter is wrongly formatted");
    it++;
    actualNode = *actualNode.getArray().at(indexArray);
    return true;
}

const bool jsonhl::Deserializer::____MgetObject(jsonhl::Value &actualNode, std::string::iterator &it) const
{
    std::string::iterator endObject = it;

    if (actualNode.getType() != jsonhl::Value::ValueType::OBJECT)
        return false;
    endObject++;
    if (*endObject == false)
        throw std::runtime_error("Object name is null");
    for (; *endObject && *endObject != '.' && *endObject != '['; endObject++)
        ;
    actualNode = *actualNode.getObject().at(std::string(it.base(), endObject.base() - it.base()));
    it = endObject;
    return true;
}

const bool jsonhl::Deserializer::____MgetInternal(std::string &buffer, jsonhl::Value &actualNode) const
{
    for (std::string::iterator it = buffer.begin(); it != buffer.end();)
    {
        switch (*it)
        {
        case '[':
            if (this->____MgetArray(actualNode, ++it) == false)
                return false;
            break;
        case '.':
            if (this->____MgetObject(actualNode, ++it) == false)
                return false;
            break;
        default:
            if (this->____MgetObject(actualNode, ++it) == false)
                return false;
            break;
        }
    }
    return true;
}

const jsonhl::Value &jsonhl::Deserializer::getValue() const
{
    return this->_value;
}
const jsonhl::Value jsonhl::Deserializer::get(std::string &buffer) const
{
    jsonhl::Value conf = this->_value;
    if (buffer.empty())
        throw std::runtime_error("Buffer is empty in jsonhl::Deserializer::has");
    if (this->getValue().getType() == jsonhl::Value::ValueType::JSONNULL)
        throw std::runtime_error("The json has wether only a null value or was not parsed yet");
    if (this->____MgetInternal(buffer, conf) == false)
        throw std::runtime_error("Could not parse buffer in jsonhl::Deserializer::has");
    return conf;
}
