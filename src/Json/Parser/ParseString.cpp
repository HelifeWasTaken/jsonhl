/**
 * File              : ParseString.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */
#include "JsonhlParser.hpp"

void jsonhl::Parser::____MJsonReadString(std::string &buffer)
{
    while (this->_buffer.at(this->_index))
    {
        if (this->_buffer.at(this->_index) == '\\')
        {
            this->_index++;
            if (!this->_buffer.at(this->_index))
                throw std::runtime_error("Got out of bounds while parsing escape code");
            switch (this->_buffer.at(this->_index))
            {
            case '"':
                buffer.append("\"");
                break;
            case '\\':
                buffer.append("\\");
                break;
            case '/':
                buffer.append("/");
                break;
            case 'b':
                buffer.append("\b");
                break;
            case 'f':
                buffer.append("\f");
                break;
            case 'n':
                buffer.append("\n");
                break;
            case 'r':
                buffer.append("\r");
                break;
            case 't':
                buffer.append("\t");
                break;
            default:
                buffer.append(1, this->_buffer.at(this->_index));
                break;
            }
            this->_index++;
            continue;
        }
        if (this->_buffer.at(this->_index) == '\"')
        {
            this->_index++;
            return;
        }
        buffer.append(1, this->_buffer.at(this->_index));
        this->_index++;
    }
    throw std::runtime_error("Expected '\"' to end the string");
}

bool jsonhl::Parser::parseString(jsonhl::Value &conf)
{
    std::string buffer;

    if (this->_buffer.at(this->_index) != '\"')
        return false;
    this->_index++;
    this->____MJsonReadString(buffer);
    conf = jsonhl::Value(buffer);
    return true;
}
