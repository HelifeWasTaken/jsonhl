/**
 * File              : ParseObject.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */
#include "JsonhlParser.hpp"

void jsonhl::Parser::____MJsonObjectReadData(jsonhl::Value::Object &object)
{
    std::shared_ptr<jsonhl::Value> value = std::make_shared<jsonhl::Value>();
    std::string key;

    this->skipSpaces();
    if (this->_buffer.at(this->_index) != '\"')
        throw std::runtime_error("Could not find the start of the Key");
    this->_index++;
    this->____MJsonReadString(key);
    this->skipSpaces();
    if (this->_buffer.at(this->_index) != ':')
        throw std::runtime_error("Could not find the ':' determing the end of the Key");
    this->_index++;
    this->skipSpaces();
    this->parseValue(*value);
    object[key] = value;
}

void jsonhl::Parser::____MJsonParseObjectLoop(jsonhl::Value &conf, jsonhl::Value::Object &objects)
{
    this->____MJsonObjectReadData(objects);
    while (this->_buffer.at(this->_index))
    {
        this->skipSpaces();
        if (this->_buffer.at(this->_index) == '}')
        {
            conf = Value(objects);
            this->_index++;
            return;
        }
        else if (this->_buffer.at(this->_index) != ',')
            throw std::runtime_error("expected ',' after value [object]");
        this->_index++;
        this->skipSpaces();
        this->____MJsonObjectReadData(objects);
    }
    throw std::runtime_error("Expected '}' at the end of the object");
}

bool jsonhl::Parser::parseObject(jsonhl::Value &conf)
{
    jsonhl::Value::Object objects;

    if (this->_buffer.at(this->_index) != '{')
        return false;
    this->_index++;
    this->skipSpaces();
    if (this->_buffer.at(this->_index) == '}')
    {
        this->_index++;
        conf = Value(objects);
        return true;
    }
    this->____MJsonParseObjectLoop(conf, objects);
    return true;
}
