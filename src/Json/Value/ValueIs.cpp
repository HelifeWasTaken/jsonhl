/**
 * File              : ValueIs.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include "JsonhlValue.hpp"

const bool jsonhl::Value::is(const jsonhl::Value::ValueType &type) const
{
    return this->getType() == type;
}
const bool jsonhl::Value::isNull() const
{
    return this->is(jsonhl::Value::ValueType::JSONNULL);
}
