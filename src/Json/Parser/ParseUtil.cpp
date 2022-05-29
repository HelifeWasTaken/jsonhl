/**
 * File              : ParseUtil.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */
#include "JsonhlParser.hpp"

bool jsonhl::Parser::isToken(char const &c, const std::string &tokens) const
{
    return tokens.find(c) != std::string::npos;
}
void jsonhl::Parser::skipSpaces()
{
    for (; this->_index < this->_buffer.size() && this->isToken(this->_buffer.at(this->_index), this->SPACES_TOKENS);
         this->_index++)
        ;
}
