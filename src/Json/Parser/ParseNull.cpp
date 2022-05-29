/**
 * File              : ParseNull.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */
#include "JsonhlParser.hpp"

bool jsonhl::Parser::parseNull(jsonhl::Value &conf)
{
    if (this->_buffer.compare(this->_index, NULL_TOKEN.size(), NULL_TOKEN) != 0)
        return false;
    this->_index += 4;
    conf = jsonhl::Value();
    return true;
}
