/**
 * File              : ParseValue.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */
#include "JsonhlParser.hpp"

void jsonhl::Parser::parseValue(jsonhl::Value &conf)
{
    this->skipSpaces();
    if (this->_buffer.at(this->_index) == false)
        return;
    else if (this->parseObject(conf) == true)
        return;
    else if (this->parseBoolean(conf) == true)
        return;
    else if (this->parseNull(conf) == true)
        return;
    else if (this->parseString(conf) == true)
        return;
    else if (this->parseNumber(conf) == true)
        return;
    else if (this->parseArray(conf) == true)
        return;
    else
        throw std::runtime_error("Invalid Json");
}
