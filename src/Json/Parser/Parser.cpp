/**
 * File              : Parser.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include "JsonhlParser.hpp"

jsonhl::Parser::Parser()
{
}

void jsonhl::Parser::unload()
{
    if (this->_buffer.empty() == false)
        this->_buffer.clear();
    this->_index = 0;
}

void jsonhl::Parser::loadBuffer(std::string &buffer)
{
    this->unload();
    this->_buffer = buffer;
    if (_buffer.empty() == true)
        throw std::runtime_error("The memory buffer is empty! File: [" + buffer + "] could not be read!");
}

jsonhl::Value jsonhl::Parser::parse()
{
    jsonhl::Value value;

    if (this->_buffer.empty())
        throw std::runtime_error("You are trying to load a Json from an empty buffer");
    try
    {
        this->parseValue(value);
    }
    catch (const std::exception &e)
    {
        this->unload();
        throw e;
    }
    this->unload();
    return value;
}
