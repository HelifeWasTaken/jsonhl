/**
 * File              : DeserializerHas.cpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 10.06.2021
 * Last Modified Date: 10.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#include "JsonhlDeserializer.hpp"

const bool jsonhl::Deserializer::has(std::string &buffer) const
{
    jsonhl::Value conf = this->_value;
    if (buffer.empty())
        throw std::runtime_error("Buffer is empty in jsonhl::Deserializer::has");
    if (this->getValue().getType() == jsonhl::Value::ValueType::JSONNULL)
        throw std::runtime_error("The json has wether only a null value or was not parsed yet");
    return this->____MgetInternal(buffer, conf);
}
