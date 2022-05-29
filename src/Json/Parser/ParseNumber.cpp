/**
 * File              : ParseNumber.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */
#include "JsonhlParser.hpp"

void jsonhl::Parser::____MJsonStrtod(double &value)
{
    if (std::isdigit(this->_buffer.at(this->_index)) == false)
        throw std::runtime_error("Invalid value while Parsing digits");
    for (; std::isdigit(this->_buffer.at(this->_index)); this->_index++)
    {
        value = value * 10 + (this->_buffer.at(this->_index) - '0');
    }
}

void jsonhl::Parser::____MJsonParseExponent(double &originalValue)
{
    bool negative = false;
    double value = 0;

    this->_index++;
    if (this->_buffer.at(this->_index) != '+')
    {
        if (this->_buffer.at(this->_index) != '-')
            throw std::runtime_error("Failed while Parsing exponent");
        negative = true;
    }
    this->_index++;
    this->____MJsonStrtod(value);
    for (auto i = 0; i < value; i++)
    {
        if (negative == true)
            originalValue /= 10;
        else
            originalValue *= 10;
    }
}

void jsonhl::Parser::____MJsonParseFloatCompletely(double &FinalValue)
{
    bool minus = false;
    double value = 0;
    double divisor = 0;
    double divided = 0;

    if (this->_buffer.at(this->_index) == '-')
    {
        this->_index++;
        minus = true;
    }
    this->____MJsonStrtod(value);
    if (this->_buffer.at(this->_index) == '.')
    {
        this->_index++;
        this->____MJsonStrtod(divisor);
        divided = divisor;
        while (divided >= 10)
            divided /= 10;
        divided /= 10;
        FinalValue = value + divided;
    }
    else if (this->_buffer.at(this->_index) == 'e' || this->_buffer.at(this->_index) == 'E')
    {
        this->____MJsonParseExponent(value);
        if (minus == true)
            value = -value;
        FinalValue = value;
    }
    else
        FinalValue = value;
}

bool jsonhl::Parser::parseNumber(jsonhl::Value &conf)
{
    bool minus = false;
    double FinalValue = 0;

    if (this->isToken(this->_buffer.at(this->_index), NUMBER_TOKENS) == false)
        return false;
    if (this->_buffer.at(this->_index) == '-')
    {
        minus = true;
        this->_index++;
    }
    this->____MJsonParseFloatCompletely(FinalValue);
    if (this->_buffer.at(this->_index) == 'e' || this->_buffer.at(this->_index) == 'E')
        this->____MJsonParseExponent(FinalValue);
    if (minus)
        FinalValue = -FinalValue;
    conf = jsonhl::Value(FinalValue);
    return true;
}
